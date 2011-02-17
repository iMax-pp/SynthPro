#ifndef PPUSHBUTTON_H
#define PPUSHBUTTON_H

#include <QGraphicsProxyWidget>

class QPushButton;

class PPushButton : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PPushButton(QString name, QGraphicsItem* parent = 0);

    void setIcon(const QIcon&);
    void setFlat(bool);

protected slots:
    void setEnabled(bool);
    void setCheckable(bool);
    void setChecked(bool);

signals:
    void buttonPushed();
    void buttonReleased();

private:
    QPushButton* m_button;
};

#endif // PPUSHBUTTON_H
