#ifndef VIRTUALPORT_H
#define VIRTUALPORT_H

#include "abstraction/buffer.h"
#include <QObject>

class Module;
class Port;
class SynthProFactory;

/**
 * Modules can be linked through their ports.
 * A virtual port can be used like a port and automatically handles (under the hood) the
 * replication of its real ports.
 */
class VirtualPort : public QObject {
    Q_OBJECT

public:
    VirtualPort(Module* parent, const QString& name, SynthProFactory*, bool replicable = false, bool gate = false);
    virtual ~VirtualPort();

    void initialize();

    /// Direction of this VirtualPort (in or out)
    virtual bool out() const = 0;

    /// @returns The Module containing this VirtualPort
    inline Module* module() const { return m_module; }

    /// @returns The name of this VirtualPort
    inline const QString& name() const { return m_name; }

    /// @returns The VirtualPorts connected to this VirtualPort
    inline const QList<Port*> connections() const { return m_connections; }

    /// @returns the (readable) Buffer of this VirtualPort
    inline Buffer* buffer() { return &m_buffer; }

    /**
     * Indicate if this port is connectable with a given port.
     * @returns true if this port is available and other port is compatible.
     * @see available, compatible
     */
    bool connectable(const VirtualPort*) const;

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
     * @invariant a.compatible(b) <=> b.compatible(a)
     */
    bool compatible(const VirtualPort* other) const;

    /// Remove a replication of this VirtualPort
    virtual bool removePort(Port*);
    /// Replicate this VirtualPort and returns the newly created Port
    virtual Port* replicate();

protected slots:
    void connection(Port*, Port*);
    void disconnection(Port*, Port*);

protected:
    Module* m_module;
    QString m_name;
    bool m_replicable;
    bool m_gate;
    QList<Port*> m_connections;
    Buffer m_buffer;
    SynthProFactory* m_factory;
};

#endif // VIRTUALPORT_H
