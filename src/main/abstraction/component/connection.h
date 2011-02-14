#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

class OutPort;
class InPort;

/**
 * This class holds a connection between two VirtualPorts.
 * It automatically adds itself to the VirtualPorts connections at creation
 * and removes itself from the VirtualPorts connections at destruction.
 */
class Connection : public QObject {
    Q_OBJECT

public:
    Connection(OutPort* source, InPort* target);
    virtual ~Connection();

    inline OutPort* source() const { return m_source; }
    inline InPort* target() const { return m_target; }

protected:
    OutPort* m_source;
    InPort* m_target;
};

#endif // CONNECTION_H