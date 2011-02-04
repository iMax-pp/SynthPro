#ifndef OUTPORT_H
#define OUTPORT_H

#include "abstraction/buffer.h"
#include "port.h"

class OutPort : public Port {
    Q_OBJECT

public:
    OutPort(Module* parent = 0);

    bool out() const;
    Buffer* buffer();
    void switchBuffers();

protected:
    Buffer m_buffer;
    Buffer m_oldBuffer;
};

#endif // OUTPORT_H
