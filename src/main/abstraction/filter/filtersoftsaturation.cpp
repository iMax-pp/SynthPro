#include "filtersoftsaturation.h"

#include "abstraction/buffer.h"
#include "abstraction/module/vcf.h"
#include "abstraction/module/vco.h"

#include <QtCore>

FilterSoftSaturation::FilterSoftSaturation()
    : m_currentResonance(0)
    , m_currentResonanceNormalized(0)
{
}

void FilterSoftSaturation::apply(Buffer* bufferIn, Buffer* bufferShaper, qreal, qreal shaperDimmer, Buffer* bufferOut)
{
    qreal* dataOut = bufferOut->data();
    qreal* dataIn = bufferIn->data();
    qreal* dataInShaper = bufferShaper->data();

    // Convert the shaper given, if it has changed.
    if (m_currentResonance != shaperDimmer) {
        m_currentResonance = shaperDimmer;
        // Normalize the resonance, from the values given by the Resonance in parameter to what we require here.
        m_currentResonanceNormalized = ((m_currentResonance - VCF::R_MIN) / VCF::R_MAX)
                                       * (SHAPER_MAX - SHAPER_MIN) + SHAPER_MIN;
    }

    for (int i = 0, size = bufferIn->length(); i < size; i++) {
        qreal shaperValue = dataInShaper[i];
        // Normalize the value read from the BufferShaper.
        shaperValue = (shaperValue + VCO::SIGNAL_INTENSITY)
                  * ((SHAPER_MAX - SHAPER_MIN) / (VCO::SIGNAL_INTENSITY * 2)) + SHAPER_MIN;
        shaperValue += m_currentResonanceNormalized;

        if (shaperValue < SHAPER_MIN) {
            shaperValue = SHAPER_MIN;
        } else if (shaperValue > SHAPER_MAX) {
            shaperValue = SHAPER_MAX;
        }

        // Soft Saturation process.
        qreal x = dataIn[i];
        bool positive = (x >= 0);
        if (!positive) {
            x = -x;
        }

        if (x > 1) {
            x = shaperValue + (x - shaperValue) /
                (1 + ((x - shaperValue) / (1 - shaperValue)) * ((x - shaperValue) / (1 - shaperValue)));
        } else if (x > shaperValue) {
            x = (shaperValue + 1) / 2;
        }

        if (!positive) {
            x = -x;
        }

        // Limit test
        x = x > INTENSITY_LIMIT ? INTENSITY_LIMIT : x;
        x = x < -INTENSITY_LIMIT ? -INTENSITY_LIMIT : x;

        dataOut[i] = x;
    }
}
