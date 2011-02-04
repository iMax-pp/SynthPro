#include "buffer.h"

#include <string.h>

Buffer::Buffer(int length)
    : m_length(length)
{
    m_data = new qreal[length];
    clear();
}

Buffer::~Buffer()
{
    delete m_data;
}

void Buffer::clear()
{
    memset(m_data, 0, length() * sizeof(qreal));
}
