#include "filterlp229.h"

#include "abstraction/buffer.h"
#include "abstraction/vco.h"

#include <QtCore>

FilterLP229::FilterLP229()
    : m_valueInM1(0)
    , m_valueInM2(0)
    , m_valueOutM1(0)
    , m_valueOutM2(0)
{
}

/// TODO : les params r et f peuvent varier au cours du temps !!!!! Il me faut plusieurs buffers d'entrées ?!

void FilterLP229::apply(Buffer* bufferIn, Buffer* bufferOut)
{
    /*
    r  = rez amount, from sqrt(2) to ~ 0.1
    f  = cutoff frequency

    out(n) = a1 * in + a2 * in(n-1) + a3 * in(n-2) - b1*out(n-1) - b2*out(n-2)

    Lowpass:
      c = 1.0 / tan(pi * f / sample_rate);

      a1 = 1.0 / ( 1.0 + r * c + c * c);
      a2 = 2* a1;
      a3 = a1;
      b1 = 2.0 * ( 1.0 - c*c) * a1;
      b2 = ( 1.0 - r * c + c * c) * a1;
    */

    const qreal f = 3000;
    const qreal r = 0.2;

    qreal* dataOut = bufferOut->data();
    qreal* dataIn = bufferOut->data();

    // TODO : Should be recalculated whenever r and f change !!!
    qreal c = 1.0 / tan(M_PI * f / VCO::REPLAY_FREQUENCY);
    qreal a1 = 1.0 / (1.0 + r * c + c * c);
    qreal a2 = 2 * a1;
    qreal a3 = a1;
    qreal b1 = 2.0 * (1.0 - c * c) * a1;
    qreal b2 = (1.0 - r * c + c * c) * a1;

    for (int i = 0, size = bufferIn->length(); i < size; i++) {
        qreal in = dataIn[i];
        qreal out = a1 * in + a2 * m_valueInM1 + a3 * m_valueInM2 - b1 * m_valueOutM1 - b2 * m_valueOutM2;
        dataOut[i] = out;

        m_valueInM2 = m_valueInM1;
        m_valueInM1 = in;

        m_valueOutM2 = m_valueOutM1;
        m_valueOutM1 = out;
    }
}
