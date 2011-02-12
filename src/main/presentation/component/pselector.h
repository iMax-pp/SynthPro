#ifndef PSELECTOR_H
#define PSELECTOR_H

#include <QButtonGroup>
#include <QGraphicsProxyWidget>

class PSelector : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PSelector(QList<QString> items, const QString& name, QGraphicsItem* parent = 0);

public slots:
    void selectButton(int idx);

signals:
    void choiceChanged(int);

private:
    QButtonGroup* m_buttonGroup;
};

#endif // PSELECTOR_H
