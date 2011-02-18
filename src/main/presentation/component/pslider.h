#ifndef PSLIDER_H
#define PSLIDER_H

#include "presentation/component/pdimmer.h"

/**
 * Concrete presentation of a PDimmer.
 * Represents a slider.
 */
class PSlider : public PDimmer {
public:
    PSlider(CDimmer*, const QString& name, int min, int max, int defaultValue,
            QGraphicsItem* parent = 0);
};

#endif // PSLIDER_H
