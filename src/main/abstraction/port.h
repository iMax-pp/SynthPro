#ifndef PORT_H
#define PORT_H

#include "abstraction/buffer.h"
#include <QObject>

class Module;

/**
 * Modules can be linked through their ports.
 */
class Port : public QObject {
    Q_OBJECT

public:
    Port(Module* parent, const QString& name, bool replicable = false, bool gate = false);
    virtual ~Port();

    /// Direction of this port (in or out)
    virtual bool out() const = 0;

    /// @returns The Module containing this Port
    inline Module* module() const { return m_module; }

    /// @returns The name of this Port
    inline const QString& name() const { return m_name; }

    /// @returns The Ports connected to this Port
    inline const QList<Port*> connections() const { return m_connections; }

    /// @returns the (readable) Buffer of this Port
    inline Buffer* buffer() { return &m_buffer; }

    /**
     * Indicate if this port is connectable with a given port.
     * @returns true if this port is available and other port is compatible.
     * @see available, compatible
     */
    bool connectable(const Port*) const;

    /**
     * Connect this port to the other port (this method will handle the both sides of the association)
     * (Does nothing if this port is not connectable to the other)
     */
    virtual void connectTo(Port* other);

    /**
     * Disconnect this port from the other port (this method handle the both sides of the association).
     * (Does nothing if this port is not connected to the other)
     */
    virtual void disconnectFrom(Port* other);

    /// Indicate if this port can be multiplexed or mixed
    inline bool replicable() const { return m_replicable; }

    /// Indicate if this port is a gate
    inline bool gate() const { return m_gate; }

signals:
    void connectionsChanged();

protected:
    /**
     * Indicate if this port is free.
     * @returns true if this port is replicable or unused, otherwise false.
     */
    bool available() const;

    /**
     * @return true if the other Port can be plugged to this Port, that is if
     * their directions are different and if they both are gates or are not.
     */
    bool compatible(const Port* other) const;

    Module* m_module;
    QString m_name;
    bool m_replicable;
    bool m_gate;
    QList<Port*> m_connections;
    Buffer m_buffer;
};

#endif // PORT_H
