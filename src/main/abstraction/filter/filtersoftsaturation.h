#ifndef FILTERSOFTSATURATION_H
#define FILTERSOFTSATURATION_H

#include "abstraction/filter/filter.h"

#include <QtCore>

/**
  * Soft saturation, from http://www.musicdsp.org/showArchiveComment.php?ArchiveID=42
  */
class FilterSoftSaturation : public Filter {
public:
    FilterSoftSaturation();

    virtual void apply(Buffer* bufferIn, Buffer* bufferInCutOff, qreal cutOffBase, qreal resonance, Buffer* bufferOut);

private:
    static const qreal SHAPER_MIN = 0.0;
    static const qreal SHAPER_MAX = 1.0;

    qreal m_currentResonance;
    qreal m_currentResonanceNormalized;
};


#endif // FILTERSOFTSATURATION_H
