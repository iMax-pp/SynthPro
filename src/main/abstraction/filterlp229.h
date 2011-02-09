#ifndef FILTERLP229_H
#define FILTERLP229_H

#include "abstraction/filter.h"

#include <QtCore>

/**
  * LP Filter, from http://www.musicdsp.org/archive.php?classid=3#229.
  */
class FilterLP229 : public Filter {
public:
    FilterLP229();

    virtual void apply(Buffer* bufferIn, Buffer* bufferInCutOff, qreal resonance, Buffer* bufferOut);

private:
    qreal m_valueInM1; // Value In T-1.
    qreal m_valueInM2; // Value In T-2.
    qreal m_valueOutM1; // Value Out T-1.
    qreal m_valueOutM2; // Value Out T-2.

    // Values calculated by the filter and need storage.
    qreal m_a1;
    qreal m_a2;
    qreal m_a3;
    qreal m_b1;
    qreal m_b2;

    qreal m_currentCutOffValue; // Useful to know if it has changed.
};

#endif // FILTERLP229_H
