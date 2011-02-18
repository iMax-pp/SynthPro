#include "pvirtualport.h"

#include "control/component/cvirtualport.h"
#include "control/component/cwire.h"
#include "presentation/component/pport.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

PVirtualPort::PVirtualPort(CVirtualPort* control, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_control(control)
    , m_label(0)
    , m_connectionsLayout(0)
{
}

void PVirtualPort::initialize(PPort* availablePort)
{
    // Create label for port.
    m_label = new TextWidget(control()->name(), this);
    m_label->setFont(QFont("Courier", 10, QFont::Normal));

    QGraphicsGridLayout* layout = new QGraphicsGridLayout(this);
    layout->setSpacing(0);

    m_connectionsLayout = new QGraphicsLinearLayout(Qt::Vertical, layout);
    m_connectionsLayout->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    m_connectionsLayout->setSpacing(4);

    if (control()->out()) {
        layout->addItem(m_label, 0, 0);
        layout->addItem(m_connectionsLayout, 0, 1);
        layout->setColumnMaximumWidth(0, m_label->size().width());
    } else {
        layout->addItem(m_connectionsLayout, 0, 0);
        layout->addItem(m_label, 0, 1);
        layout->setColumnMaximumWidth(1, m_label->size().width());
    }

    m_connectionsLayout->addItem(availablePort);

    m_connectionsLayout->activate();
    layout->activate();
}

void PVirtualPort::insertConnectionPort(int i, PPort* port)
{
    m_connectionsLayout->insertItem(i, port);

    m_connectionsLayout->activate();
    layout()->activate();
}

void PVirtualPort::removeConnectionPort(PPort* port)
{
    m_connectionsLayout->removeItem(port);

    m_connectionsLayout->activate();
    layout()->activate();

    port->deleteLater();
}
