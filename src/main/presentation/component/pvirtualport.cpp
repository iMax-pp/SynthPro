#include "pvirtualport.h"

#include "control/component/cvirtualport.h"
#include "control/component/cwire.h"
#include "presentation/component/pport.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsLinearLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

PVirtualPort::PVirtualPort(CVirtualPort* control, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_control(control)
    , m_label(0)
    , m_connectionsLayout(0)
    , m_portsLayout(0)
{
}

void PVirtualPort::initialize(PPort* availablePort)
{
    // Create label for port.
    m_label = new TextWidget(control()->name(), this);
    m_label->setFont(QFont("Courier", 10, QFont::Normal));

    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    layout->setSpacing(0);
    m_portsLayout = new QGraphicsLinearLayout(Qt::Vertical, layout);
    m_portsLayout->setSpacing(4);
    m_connectionsLayout = new QGraphicsLinearLayout(Qt::Vertical, m_portsLayout);
    m_connectionsLayout->setSpacing(4);

    if (control()->out()) {
        layout->addItem(m_label);
        layout->addItem(m_portsLayout);
    } else {
        layout->addItem(m_portsLayout);
        layout->addItem(m_label);
    }
    m_portsLayout->addItem(m_connectionsLayout);
    m_portsLayout->addItem(availablePort);

    setMinimumSize(boundingRect().size());
}

void PVirtualPort::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
}

QRectF PVirtualPort::boundingRect() const
{
    return childrenBoundingRect();
}

void PVirtualPort::addConnectionPort(PPort* port)
{
    m_connectionsLayout->addItem(port);
}

void PVirtualPort::removeConnectionPort(PPort* port)
{
    m_connectionsLayout->removeItem(port);
    delete port;
}
