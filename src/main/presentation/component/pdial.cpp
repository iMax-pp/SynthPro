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
    m_selector = new QDial;
    m_selector->setNotchesVisible(true);
    m_selector->setRange(min, max);
    m_selector->setValue(defaultValue);
    vbox->addWidget(m_selector);

    m_box->setLayout(vbox);
    setMaximumSize(80, 80);

    connect(m_selector, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

void PDial::setValue(int value)
{
    m_selector->setValue(value);
    update();
}
