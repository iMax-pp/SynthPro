#include "port.h"

#include "abstraction/virtualport.h"

Port::Port(VirtualPort* vPort)
    : QObject(vPort)
    , m_vPort(vPort)
    , m_connection(0)
{
}

bool Port::connect(Port* other)
{
    if (vPort()->connectable(other->vPort())) {
        this->_connect(other);
        other->_connect(this);

        qDebug(QString("VirtualPort::connect() %1 -> %2").arg(vPort()->name()).arg(other->vPort()->name()).toLatin1());

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
    if (m_connection && m_connection->m_connection == m_connection) {
        qDebug(QString("VirtualPort::disconnect() %1 - %2").arg(vPort()->name()).arg(m_connection->vPort()->name()).toLatin1());

        m_connection->_disconnect();
        this->_disconnect();

        return true;
    }
    return false;
}

void Port::_disconnect()
{
    emit disconnected(this, m_connection);
    m_connection = 0;
}
