#ifndef BUFFER_H
#define BUFFER_H

#include <QtGlobal>

class Buffer {
public:
    static const int DEFAULT_LENGTH = 256;

    /**
     * Constructs a buffer of a given length, initializing its content to 0.
     */
    Buffer(int length = DEFAULT_LENGTH);
    Buffer(const Buffer& source);
    ~Buffer();

    /// Direct access to the raw data of this Buffer
    inline qreal* data() const { return m_data; }

    /// @returns The length of this buffer
    inline int length() const { return m_length; }

    /// add a float to all buffer's values
    void add(const qreal);

    /// Fill this buffer with 0
    void clear();

protected:
    qreal* m_data;
    int m_length;
};

#endif // BUFFER_H
