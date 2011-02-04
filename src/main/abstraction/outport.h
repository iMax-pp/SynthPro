#ifndef OUT_H
#define OUT_H

#include "port.h"
#include "abstraction/buffer.h"

class OutPort : public Port {
    Q_OBJECT

public:
    OutPort(Module* parent = 0);

    bool out() const;
    Buffer* buffer();

protected:
    Buffer m_buffer;
    Buffer m_oldBuffer;
};

#endif // OUT_H
