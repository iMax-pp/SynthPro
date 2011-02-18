#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

class OutPort;
class InPort;

/**
 * This class holds a connection between two VirtualPorts.
 * It <strong>automatically</strong> adds itself to the VirtualPorts connections
 * at creation and removes itself from the VirtualPorts connections at destruction.
 */
class Connection : public QObject {
    Q_OBJECT

public:
    /// Constructs a connection between the given source OutPort and target InPort.
    Connection(OutPort* source, InPort* target);
    virtual ~Connection();

    /// @returns the source OutPort.
    inline OutPort* source() const { return m_source; }
    /// @returns the target InPort.
    inline InPort* target() const { return m_target; }

protected:
    OutPort* m_source;
    InPort* m_target;
};

#endif // CONNECTION_H
