#ifndef INPORT_H
#define INPORT_H

#include "port.h"

class InPort : public virtual Port {
    Q_OBJECT

public:
    InPort(Module* parent, bool replicable = false, bool gate = false);
    ~InPort();

    /**
     * Fetch data from the connections.
     * If this port is replicable, it mixes its inputs
     */
    void fetch();

    // Overriden methods of Module
    bool out() const;
    Buffer* buffer();

protected:
    Buffer* m_buffer;
};

#endif // INPORT_H
