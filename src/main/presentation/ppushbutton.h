#ifndef PPUSHBUTTON_H
#define PPUSHBUTTON_H

#include <QGraphicsProxyWidget>

class PPushButton : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PPushButton(QString name, QGraphicsItem* parent = 0);

signals:
    void buttonPushed();
    void buttonReleased();
};

#endif // PPUSHBUTTON_H
