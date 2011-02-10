#ifndef VIRTUALPORT_H
#define VIRTUALPORT_H

#include "abstraction/buffer.h"
#include <QObject>

class Module;

/**
 * Modules can be linked through their ports.
 */
class VirtualPort : public QObject {
    Q_OBJECT

public:
    VirtualPort(Module* parent, const QString& name, bool replicable = false, bool gate = false);
    virtual ~VirtualPort();

    /// Direction of this VirtualPort (in or out)
    virtual bool out() const = 0;

    /// @returns The Module containing this VirtualPort
    inline Module* module() const { return m_module; }

    /// @returns The name of this VirtualPort
    inline const QString& name() const { return m_name; }

    /// @returns The VirtualPorts connected to this VirtualPort
    inline const QList<VirtualPort*> connections() const { return m_connections; }

    /// @returns the (readable) Buffer of this VirtualPort
    inline Buffer* buffer() { return &m_buffer; }

    /**
     * Indicate if this port is connectable with a given port.
     * @returns true if this port is available and other port is compatible.
     * @see available, compatible
     */
    bool connectable(const VirtualPort*) const;

    /**
     * Connect this port to the other port (this method will handle the both sides of the association)
     * (Does nothing if this port is not connectable to the other)
     */
    virtual void connectTo(VirtualPort* other);

    /**
     * Disconnect this port from the other port (this method handle the both sides of the association).
     * (Does nothing if this port is not connected to the other)
     */
    virtual void disconnectFrom(VirtualPort* other);

    /// Indicate if this VirtualPort can be multiplexed or mixed
    inline bool replicable() const { return m_replicable; }

    /// Indicate if this port is a gate
    inline bool gate() const { return m_gate; }

signals:
    void connectionsChanged();

protected:
    /**
     * Indicate if this VirtualPort is free.
     * @returns true if this VirtualPort is replicable or unused, otherwise false.
     */
    bool available() const;

    /**
     * @return true if the other VirtualPort can be plugged to this VirtualPort, that is if
     * their directions are different and if they both are gates or are not.
     */
    bool compatible(const VirtualPort* other) const;

    Module* m_module;
    QString m_name;
    bool m_replicable;
    bool m_gate;
    QList<VirtualPort*> m_connections;
    Buffer m_buffer;
};

#endif // VIRTUALPORT_H
