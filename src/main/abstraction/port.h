#ifndef PORT_H
#define PORT_H

#include <QObject>

class Module;
class Buffer;

/**
 * Modules can be linked through their ports.
 */
class Port : public QObject {
    Q_OBJECT

public:
    Port(Module* parent, bool replicable = false, bool gate = false);
    virtual ~Port();

    /// Direction of this port (in or out)
    virtual bool out() const = 0;

    /**
     * Buffer of this Port.
     * @returns 0 if this port does not have a buffer (e.g. an unconnected input port)
     */
    virtual Buffer* buffer() = 0;

    /// @returns The Module containing this Port
    inline Module* module() const { return m_module; }

    /// @returns The Ports connected to this Port (FIXME is it safe?)
    inline const QList<Port*> connections() const { return m_connections; }

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
    void connectTo(Port* other);

    /**
     * Disconnect this port from the other port (this method handle the both sides of the association).
     * (Does nothing if this port is not connected to the other)
     */
    void disconnectFrom(Port* other);

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
    bool m_replicable;
    bool m_gate;
    QList<Port*> m_connections;
};

#endif // PORT_H
