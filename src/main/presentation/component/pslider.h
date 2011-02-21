#ifndef PSLIDER_H
#define PSLIDER_H

#include "presentation/component/pdimmer.h"

class QSlider;

/**
 * Concrete presentation of a PDimmer.
 * Represents a slider.
 */
class PSlider : public PDimmer {
public:
    PSlider(CDimmer*, const QString& name, int min, int max, int defaultValue,
            QGraphicsItem* parent = 0);

    void setValue(int);

private:
    QSlider* m_selector;
};

#endif // PSLIDER_H
