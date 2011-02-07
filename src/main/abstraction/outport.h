#ifndef OUTPORT_H
#define OUTPORT_H

#include "abstraction/buffer.h"
#include "port.h"

class OutPort : public virtual Port {
    Q_OBJECT

public:
    OutPort(Module* parent, bool replicable = false, bool gate = false);
    ~OutPort();

    bool out() const;
    Buffer* buffer();
    void swapBuffers();

protected:
    Buffer* m_buffer;
    Buffer* m_oldBuffer;
};

#endif // OUTPORT_H
