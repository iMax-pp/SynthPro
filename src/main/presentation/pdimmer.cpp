#include "pdimmer.h"

#include "control/cdimmer.h"
#include <QDial>

PDimmer::PDimmer(CDimmer* control, int min, int max, int value, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
{
    // Create a Selector.
    QDial* selector = new QDial;
    selector->setNotchesVisible(true);
    selector->setRange(min, max);
    selector->setValue(value);

    // Connect the widget value change to control.
    connect(selector, SIGNAL(valueChanged(int)), control, SLOT(valueChanged(int)));

    // Add it.
    setWidget(selector);
}
