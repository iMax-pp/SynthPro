#include "port.h"

#include "abstraction/component/virtualport.h"

#include <QDebug>

Port::Port(VirtualPort* vPort)
    : QObject(vPort)
    , m_vPort(vPort)
    , m_connection(0)
{
}

Port::~Port()
{
}

bool Port::connect(Port* other)
{
    if (vPort()->connectable(other->vPort())) {
        this->_connect(other);
        other->_connect(this);

        qDebug() << "Port::connect()" << vPort()->name() << "->" << other->vPort()->name();

        return true;
    }
    return false;
}

void Port::_connect(Port* other)
{
    // If this port was already connected to another one, disconnect it
    disconnect();
    m_connection = other;

    emit connected(this, other);
}

bool Port::disconnect()
{
    if (connected()) {
        qDebug() << "Port::disconnect()" << vPort()->name() << "-" << m_connection->vPort()->name();

        m_connection->_disconnect();
        this->_disconnect();

        return true;
    }
    return false;
}

void Port::_disconnect()
{
    Port* target = m_connection;
    m_connection = 0;
    emit disconnected(this, target);
}
