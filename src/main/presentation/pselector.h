#ifndef PSELECTOR_H
#define PSELECTOR_H

#include <QGraphicsProxyWidget>

class PSelector : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PSelector(QList<QString> items, const QString& name, QGraphicsItem* parent = 0);

signals:
    void choiceChanged(int);
};

#endif // PSELECTOR_H
