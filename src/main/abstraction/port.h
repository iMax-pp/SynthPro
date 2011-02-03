#ifndef PORT_H
#define PORT_H

#include <QObject>

/**
 * Modules can be linked through their ports.
 */
class Port : public QObject
{
    Q_OBJECT

public:
    Port(QObject* parent, bool replicable = false, bool gate = false);
    virtual ~Port();

    /// Indicate if this port is a gate
    inline virtual bool gate() const { return m_gate; }

    /// Direction of this port (in or out)
    virtual bool out() const = 0;

    /// Indicate if this port is connected to another one
    virtual bool connected() const;
    /**
     * Indicate if this port is compatible with a given port.
     * @returns true if this port is not connected and its direction
     * is different from others direction and they both are gate or are not.
     */
    virtual bool isConnectable(const Port*) const;
    /// Connect this port to the other port (this method will handle the both side of the association)
    virtual void connectTo(Port*);

    /// Indicate if this port can be multiplexed or mixed
    inline virtual bool replicable() const { return m_replicable; }

    //virtual Buffer buffer();

signals:
    void connectedChanged(bool);

private:
    bool m_replicable;
    bool m_gate;
    Port* m_connection;
};

#endif // PORT_H
