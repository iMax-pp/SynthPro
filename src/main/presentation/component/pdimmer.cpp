#include "pdimmer.h"

#include "control/component/cdimmer.h"
#include <QDial>
#include <QGroupBox>
#include <QVBoxLayout>

PDimmer::PDimmer(const QString& name, int min, int max, int defaultValue, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
    , m_name(name)
{
    m_box = new QGroupBox;
    m_box->setAlignment(Qt::AlignHCenter);
    m_box->setFlat(true);

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setMargin(0);

    // Create a Selector.
    QDial* selector = new QDial;
    selector->setNotchesVisible(true);
    selector->setRange(min, max);
    selector->setValue(defaultValue);
    vbox->addWidget(selector);

    m_box->setLayout(vbox);
    changeTitle(selector->value());

    connect(selector, SIGNAL(valueChanged(int)), this, SLOT(changeTitle(int)));
    connect(selector, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    // Add it.
    setWidget(m_box);
}

void PDimmer::changeTitle(int value)
{
    m_box->setTitle(m_name + " (" + QString::number(value / CDimmer::DISCR) + ")");
}
