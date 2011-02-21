#include "pslider.h"

#include <QGroupBox>
#include <QSlider>
#include <QVBoxLayout>

PSlider::PSlider(CDimmer* control, const QString& name, int min, int max, int defaultValue,
                 QGraphicsItem* parent)
    : PDimmer(control, name, parent)
{
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMargin(0);
    
    // Create a Selector.
    m_selector = new QSlider(Qt::Horizontal);
    m_selector->setRange(min, max);
    m_selector->setValue(defaultValue);
    vbox->addWidget(m_selector);

    m_box->setLayout(vbox);
    setMaximumSize(140, 40);

    connect(m_selector, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

}

void PSlider::setValue(int value)
{
    m_selector->setValue(value);
    update();
}
