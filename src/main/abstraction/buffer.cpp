#include "buffer.h"

#include <string.h>

Buffer::Buffer(int length)
    : m_length(length)
{
    m_data = new qreal[m_length];
    clear();
}

Buffer::Buffer(const Buffer& source)
    : m_length(source.length())
{
    m_data = new qreal[m_length];
    memcpy(m_data, source.m_data, m_length * sizeof(*m_data));
}

Buffer::~Buffer()
{
    delete m_data;
}

void Buffer::clear()
{
    memset(m_data, 0, length() * sizeof(qreal));
}

void Buffer::add(const qreal k)
{
    for (int i = 0; i < m_length; i++) {
        m_data[i] += k;
    }
}

void Buffer::mul(const qreal gain)
{
    for (int i = 0; i < m_length; i++) {
        m_data[i] = gain * m_data[i];
    }
}
