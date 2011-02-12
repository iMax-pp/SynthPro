#ifndef PORT_H
#define PORT_H

#include <QObject>

class VirtualPort;

class Port : public QObject {
    Q_OBJECT

public:
    Port(VirtualPort*);
    virtual ~Port();

    inline VirtualPort* vPort() const { return m_vPort; }

    /// @invariant connected() => connection()->connection() == this
    inline Port* connection() const { return m_connection; }

    inline bool connected() const { return m_connection; }

    /**
     * Connect this port to another port.
     * If this Port is already connected to another one, it is first disconnected.
     * Does nothing if they are not connectable.
     * @return true if the connection was successful (i.e. the ports are “connectable”)
     */
    virtual bool connect(Port*);

    /**
     * Disconnect this Port.
     * Does nothing if it were not connected.
     * @return true if the operation was successful
     */
    virtual bool disconnect();

signals:
    void connected(Port*, Port*);
    void disconnected(Port*, Port*);

protected:
    VirtualPort* m_vPort;
    Port* m_connection;

    /// Performs this side of the connection
    virtual void _connect(Port*);
    /// Performs this side of the disconnection
    virtual void _disconnect();
};

#endif // PORT_H
