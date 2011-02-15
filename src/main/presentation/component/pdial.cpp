#include "pdial.h"

#include <QDial>
#include <QGroupBox>
#include <QVBoxLayout>

PDial::PDial(CDimmer* control, const QString& name, int min, int max, int defaultValue,
             QGraphicsItem* parent)
    : PDimmer(control, name, parent)
{
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMargin(0);

    // Create a Selector.
    QDial* selector = new QDial;
    selector->setNotchesVisible(true);
    selector->setRange(min, max);
    selector->setValue(defaultValue);
    vbox->addWidget(selector);

    m_box->setLayout(vbox);
    // updateTitle(selector->value());
    setMaximumSize(80, 80);

    connect(selector, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));    
}
