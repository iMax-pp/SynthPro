#ifndef FILTERLP229_H
#define FILTERLP229_H

#include "abstraction/filter.h"

#include <QtCore>

/**
  * LP Filter, from http://www.musicdsp.org/archive.php?classid=3#229.
  * Not tested yet...
  * What is the LP slope ?
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
};

#endif // FILTERLP229_H
