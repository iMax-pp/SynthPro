#include "pdimmer.h"

#include "control/cdimmer.h"
#include <QDial>

PDimmer::PDimmer(int min, int max, int value, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
{
    // Create a Selector.
    QDial* selector = new QDial;
    selector->setNotchesVisible(true);
    selector->setRange(min, max);
    selector->setValue(value);

    connect(selector, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    // Add it.
    setWidget(selector);
}
