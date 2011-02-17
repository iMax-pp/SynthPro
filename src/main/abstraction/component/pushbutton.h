#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>

class PushButton : public QObject {
    Q_OBJECT

public:
    PushButton(QObject* parent = 0);

    inline bool pushed() const { return m_pushed; }
    inline bool isEnabled() const { return m_enabled; }
    inline bool isCheckable() const { return m_checkable; }
    inline bool isChecked() const { return m_checked; }

public slots:
    void push();
    void release();
    void setEnabled(bool);
    void setCheckable(bool);
    void setChecked(bool);

signals:
    void buttonPushed();
    void buttonReleased();
    void buttonEnabled(bool);
    void buttonCheckable(bool);
    void buttonChecked(bool);

private:
    bool m_pushed;
    bool m_enabled;
    bool m_checkable;
    bool m_checked;
};

#endif // PUSHBUTTON_H
