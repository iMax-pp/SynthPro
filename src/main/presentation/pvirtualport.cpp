#include "pvirtualport.h"

#include "control/cvirtualport.h"
#include "control/cwire.h"
#include "presentation/pport.h"
#include "presentation/textwidget.h"
#include <QFont>
#include <QGraphicsLinearLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

PVirtualPort::PVirtualPort(CVirtualPort* control, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_control(control)
    , m_label(0)
    , m_portsLayout(0)
{
    // Create label for port.
    m_label = new TextWidget(control->name(), this);
    // m_label->setPen(Qt::NoPen);
    // m_label->setBrush(style->standardPalette().brush(QPalette::ButtonText));
    m_label->setFont(QFont("Courier", 10, QFont::Normal));

    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    m_portsLayout = new QGraphicsLinearLayout(Qt::Vertical, layout);

    if (control->out()) { // Oops some logic in the presentation! I’m so crappy.
        layout->addItem(m_label);
        layout->addItem(m_portsLayout);
    } else {
        layout->addItem(m_portsLayout);
        layout->addItem(m_label);
    }

    setMinimumSize(boundingRect().size());
}

void PVirtualPort::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
}

QRectF PVirtualPort::boundingRect() const
{
    return childrenBoundingRect();
}

void PVirtualPort::addReplication(PPort* replication)
{
    m_portsLayout->addItem(replication);
}
