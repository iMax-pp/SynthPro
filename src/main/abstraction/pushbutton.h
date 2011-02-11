#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>

class Buffer;

class PushButton : public QObject {
public:
    PushButton(QObject* parent = 0);

    Buffer* buffer() const;

    void push();
    void release();

private:
    Buffer* m_buffer;
};

#endif // PUSHBUTTON_H
