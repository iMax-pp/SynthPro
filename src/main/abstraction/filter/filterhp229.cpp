#include "filterhp229.h"

#include "abstraction/buffer.h"
#include "abstraction/module/vcf.h"
#include "abstraction/module/vco.h"

#include <QtCore>

FilterHP229::FilterHP229()
    : m_valueInM1(0)
    , m_valueInM2(0)
    , m_valueOutM1(0)
    , m_valueOutM2(0)
    , m_a1(0)
    , m_a2(0)
    , m_a3(0)
    , m_b1(0)
    , m_b2(0)
    , m_currentCutOffValue(-1000)
    , m_currentCutOffBase(-1000)
    , m_currentResonance(-1000)
    , m_currentResonanceNormalized(RESONANCE_MIN)
    , m_mustRecalculateFilter(true)
{
}

void FilterHP229::apply(Buffer* bufferIn, Buffer* bufferInCutOff, qreal cutOffBase, qreal resonance, Buffer* bufferOut)
{
    /*
    r  = rez amount, from sqrt(2) to ~ 0.1
    f  = cutoff frequency

    out(n) = a1 * in + a2 * in(n-1) + a3 * in(n-2) - b1*out(n-1) - b2*out(n-2)

    Highpass. Base algorithm :
      c = tan(pi * f / sample_rate);

      a1 = 1.0 / ( 1.0 + r * c + c * c);
      a2 = -2*a1;
      a3 = a1;
      b1 = 2.0 * ( c*c - 1.0) * a1;
      b2 = ( 1.0 - r * c + c * c) * a1;

      Optimised (not used, doesn't sound as good) :
        c = tan(pi * f / sample_rate);

        c = ( c + r ) * c;
        a1 = 1.0 / ( 1.0 + c );
        b1 = ( 1.0 - c );

        out(n) = ( a1 * out(n-1) + in - in(n-1) ) * b1;
    */

    qreal* dataOut = bufferOut->data();
    qreal* dataIn = bufferIn->data();
    qreal* dataInCutOff = bufferInCutOff->data();

    // Convert the resonance given, if it has changed.
    if (m_currentResonance != resonance) {
        m_currentResonance = resonance;
        // Normalize the resonance, from the values given by the Resonance in parameter to what we require here.
        m_currentResonanceNormalized = ((m_currentResonance - VCF::R_MIN) / VCF::R_MAX)
                                       * (RESONANCE_MAX - RESONANCE_MIN) + RESONANCE_MIN;
        m_mustRecalculateFilter = true;
    }

    // If the CutOffBase has changed, force recalculation of the filter.
    if (m_currentCutOffBase != cutOffBase) {
        m_currentCutOffBase = cutOffBase;
        m_mustRecalculateFilter = true;
    }

    for (int i = 0, size = bufferIn->length(); i < size; i++) {
        // Check if the input CutOffBuffer delivers a different CutOff frequency.
        // If yes, must recalculate the filter parameters.
        if (m_mustRecalculateFilter || (dataInCutOff[i] != m_currentCutOffValue)) {
            m_currentCutOffValue = dataInCutOff[i];
            // Convert a signal into a frequency from MIN_FREQUENCY to MAX_FREQUENCY.
            qreal f = (m_currentCutOffValue + VCO::SIGNAL_INTENSITY)
                      * ((MAX_FREQUENCY - MIN_FREQUENCY) / (VCO::SIGNAL_INTENSITY * 2)) + MIN_FREQUENCY;
            f += cutOffBase;

            if (f < MIN_FREQUENCY) {
                f = MIN_FREQUENCY;
            } else if (f > MAX_FREQUENCY) {
                f = MAX_FREQUENCY;
            }

            // Filter factors calculation.
            qreal c = tan(M_PI * f / VCO::REPLAY_FREQUENCY);
            m_a1 = 1.0 / (1.0 + m_currentResonanceNormalized * c + c * c);
            m_a2 = -2 * m_a1;
            m_a3 = m_a1;
            m_b1 = 2.0 * (c * c - 1.0) * m_a1;
            m_b2 = (1.0 - m_currentResonanceNormalized * c + c * c) * m_a1;

            m_mustRecalculateFilter = false;
        }

        // Process the filter.
        qreal in = dataIn[i];
        qreal out = m_a1 * in + m_a2 * m_valueInM1 + m_a3 * m_valueInM2 - m_b1 * m_valueOutM1 - m_b2 * m_valueOutM2;

        // Limit test
        out = out > INTENSITY_LIMIT ? INTENSITY_LIMIT : out;
        out = out < -INTENSITY_LIMIT ? -INTENSITY_LIMIT : out;

        dataOut[i] = out;

        m_valueInM2 = m_valueInM1;
        m_valueInM1 = in;

        m_valueOutM2 = m_valueOutM1;
        m_valueOutM1 = out;
    }
}
