#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>

class PushButton : public QObject {
    Q_OBJECT

public:
    PushButton(QObject* parent = 0);

    inline bool pushed() const { return m_pushed; }

public slots:
    void push();
    void release();

signals:
    void buttonPushed();
    void buttonReleased();

private:
    bool m_pushed;
};

#endif // PUSHBUTTON_H
