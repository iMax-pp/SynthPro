#ifndef PDIMMER_H
#define PDIMMER_H

#include <QGraphicsProxyWidget>

class CDimmer;

class PDimmer : public QGraphicsProxyWidget {
public:
    PDimmer(CDimmer*, qreal min, qreal max, qreal defaultValue, QGraphicsItem* parent = 0);
};

#endif // PDIMMER_H
