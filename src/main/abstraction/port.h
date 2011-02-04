#ifndef PORT_H
#define PORT_H

#include <QObject>

class Module;

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

    /// @returns The Module containing this Port
    inline Module* module() const { return m_module; }

    /// @returns The Port connected to this Port (0 if not connected)
    inline Port* connection() const { return m_connection; }

    /// Indicate if this port is connected to another one
    inline bool connected() const { return m_connection; }
    /**
     * Indicate if this port is connectable with a given port.
     * @returns true if this port is not already connected and its direction
     * is different from other's direction and they both are gate or are not.
     */
    bool isConnectable(const Port*) const;
    /// Connect this port to the other port (this method will handle the both side of the association)
    void connectTo(Port*);

    /// Indicate if this port can be multiplexed or mixed
    inline bool replicable() const { return m_replicable; }

    /// Indicate if this port is a gate
    inline bool gate() const { return m_gate; }

    // virtual Buffer buffer();

signals:
    void connectedChanged(bool);

protected:
    Module* m_module;
    bool m_replicable;
    bool m_gate;
    Port* m_connection;
};

#endif // PORT_H
