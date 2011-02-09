#ifndef PDIMMER_H
#define PDIMMER_H

#include <QGraphicsProxyWidget>

class CDimmer;

class PDimmer : public QGraphicsProxyWidget {
    Q_OBJECT

public:
    PDimmer(QString name, int min, int max, int defaultValue, QGraphicsItem* parent = 0);

signals:
    void valueChanged(int);
};

#endif // PDIMMER_H
