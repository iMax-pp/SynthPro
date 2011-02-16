#ifndef FILTERHP229_H
#define FILTERHP229_H

#include "abstraction/filter/filter.h"

#include <QtCore>

/**
  * HP Filter, from http://www.musicdsp.org/archive.php?classid=3#229.
  */
class FilterHP229 : public Filter {
public:
    FilterHP229();

    virtual void apply(Buffer* bufferIn, Buffer* bufferInCutOff, qreal cutOffBase, qreal resonance, Buffer* bufferOut);

public:
    static const qreal MAX_FREQUENCY = 8000; // Highest frequency of the High Pass.
    static const qreal MIN_FREQUENCY = 30; // Lower doesn't sound nice.

private:
    static const qreal RESONANCE_MIN = 0.1;
    static const qreal RESONANCE_MAX = 1.0;

    qreal m_valueInM1; // Value In T-1.
    qreal m_valueInM2; // Value In T-2.
    qreal m_valueOutM1; // Value Out T-1.
    qreal m_valueOutM2; // Value Out T-2.

    // Values calculated by the filter and needing storage.
    qreal m_a1;
    qreal m_a2;
    qreal m_a3;
    qreal m_b1;
    qreal m_b2;

    qreal m_currentCutOffValue; // Useful to know if it has changed.
    qreal m_currentCutOffBase;
    qreal m_currentResonance;
    qreal m_currentResonanceNormalized;
    bool m_mustRecalculateFilter;
};

#endif // FILTERHP229_H
