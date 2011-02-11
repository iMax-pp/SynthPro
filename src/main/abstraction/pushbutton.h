#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>

class Buffer;

class PushButton : public QObject {
    Q_OBJECT

public:
    PushButton(QObject* parent = 0);
    virtual ~PushButton();

    Buffer* buffer() const;

public slots:
    void push();
    void release();

signals:
    void buttonPushed();
    void buttonReleased();

private:
    Buffer* m_buffer;
};

#endif // PUSHBUTTON_H
