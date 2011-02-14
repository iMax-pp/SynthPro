#include "pdimmer.h"

#include "control/component/cdimmer.h"
#include <QGroupBox>
#include <QLayout>

PDimmer::PDimmer(CDimmer* control, const QString& name, QGraphicsItem* parent)
    : QGraphicsProxyWidget(parent)
    , m_control(control)
    , m_name(name)
{
    m_box = new QGroupBox;
    m_box->setAlignment(Qt::AlignLeft);
    m_box->setFlat(true);

    // Add it.
    setWidget(m_box);
}

void PDimmer::changeTitle(int value)
{
    qreal realVal = m_control->realValue(value / CDimmer::DISCR);
    m_box->setTitle(m_name + ": " + QString::number(realVal, 'g', 3));
}
