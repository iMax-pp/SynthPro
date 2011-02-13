#include "pdimmer.h"

#include "control/component/cdimmer.h"
#include <QDial>
#include <QGroupBox>
#include <QVBoxLayout>

PDimmer::PDimmer(QString name, int min, int max, int defaultValue, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
{
    QGroupBox* group = new QGroupBox(name);
    group->setAlignment(Qt::AlignHCenter);
    group->setFlat(true);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMargin(0);

    // Create a Selector.
    QDial* selector = new QDial;
    selector->setNotchesVisible(true);
    selector->setRange(min, max);
    selector->setValue(defaultValue);
    vbox->addWidget(selector);

    group->setLayout(vbox);

    connect(selector, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    // Add it.
    setWidget(group);
}
