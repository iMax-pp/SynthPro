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
    void setEnabled(bool);

signals:
    void buttonPushed();
    void buttonReleased();
    void buttonEnabled(bool);

private:
    bool m_pushed;
    bool m_enabled;
};

#endif // PUSHBUTTON_H
