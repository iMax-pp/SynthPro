#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>

/**
 * A PushButton is an abstraction of "visual" PushButton.
 * It allows to be pushed, enabled/disabled, checkable and then checked.
 */
class PushButton : public QObject {
    Q_OBJECT

public:
    PushButton(QObject* parent = 0);

    /// @returns the push state of the button.
    inline bool pushed() const { return m_pushed; }

    /// @returns true if the button is enabled (clickable).
    inline bool isEnabled() const { return m_enabled; }

    /// @returns true if the button is clickable.
    inline bool isCheckable() const { return m_checkable; }

    /// @returns the check state of the button.
    inline bool isChecked() const { return m_checked; }

public slots:
    /// Push the button.
    void push();

    /// Release the button.
    void release();

    /// Enable or disable the button.
    void setEnabled(bool);

    /// Set the checkability state of the button.
    void setCheckable(bool);

    /// Check or uncheck the button (only if isCheckable).
    void setChecked(bool);

signals:
    /// Signal trigerred when button is pushed.
    void buttonPushed();

    /// Signal trigerred when button is released.
    void buttonReleased();

    /// Signal trigerred when button is enabled (or disabled).
    void buttonEnabled(bool);

    /// Signal trigerred when button checkability state is set.
    void buttonCheckable(bool);

    /// Signal trigerred when button is checked (or unchecked).
    void buttonChecked(bool);

private:
    bool m_pushed;
    bool m_enabled;
    bool m_checkable;
    bool m_checked;
};

#endif // PUSHBUTTON_H
