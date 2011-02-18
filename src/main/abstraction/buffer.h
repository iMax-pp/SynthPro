#ifndef BUFFER_H
#define BUFFER_H

#include <QtGlobal>

class Buffer {
public:
    /// Default length of a Buffer.
    static const int DEFAULT_LENGTH = 900;

    /// Constructs a buffer of a given length, initializing its content to 0.
    explicit Buffer(int length = DEFAULT_LENGTH);
    /// Copy constructor.
    Buffer(const Buffer& source);
    ~Buffer();

    /// Direct access to the raw data of this Buffer.
    inline qreal* data() const { return m_data; }

    /// @returns The length of this Buffer.
    inline int length() const { return m_length; }

    /// add a float to all Buffer's values.
    void add(const qreal);

    /// multiply all Buffer's value by a real.
    void mul(const qreal);

    /// Fill the Buffer with 0.
    void clear();

protected:
    qreal* m_data;
    int m_length;
};

#endif // BUFFER_H
