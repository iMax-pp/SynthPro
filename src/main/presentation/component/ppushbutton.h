#ifndef PPUSHBUTTON_H
#define PPUSHBUTTON_H

#include <QGraphicsProxyWidget>

class QPushButton;

/**
 * Presentation of the PushButton.
 */
class PPushButton : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PPushButton(QString name, QGraphicsItem* parent = 0);

    /// Change text with a given icon (of size 16x16).
    void setIcon(const QIcon&);

    /// Shape it flat (or not).
    void setFlat(bool);

protected slots:
    /// Called to visually enable or disable the PushButton.
    void setEnabled(bool);
    /// Called to visually make checkable (or not) the PushButton.
    void setCheckable(bool);
    /// Called to visually check or uncheck the PushButton.
    void setChecked(bool);

signals:
    /// Triggered when button is pushed.
    void buttonPushed();
    /// Triggered when button is released.
    void buttonReleased();

private:
    QPushButton* m_button;
};

#endif // PPUSHBUTTON_H
