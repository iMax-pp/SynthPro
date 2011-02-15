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
    QSlider* selector = new QSlider(Qt::Horizontal);
    selector->setRange(min, max);
    selector->setValue(defaultValue);
    vbox->addWidget(selector);
    
    m_box->setLayout(vbox);
    // updateTitle(selector->value());
    setMaximumSize(140, 40);

    connect(selector, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

}
