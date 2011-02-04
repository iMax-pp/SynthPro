#include "buffer.h"

#include <string.h>

Buffer::Buffer(int length)
    : m_length(length)
{
    m_data = new qreal[length];
    memset(m_data, 0, length * sizeof(qreal));
}

Buffer::~Buffer()
{
    delete m_data;
}
