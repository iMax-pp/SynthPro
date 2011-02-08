#ifndef PDIMMER_H
#define PDIMMER_H

#include <QGraphicsProxyWidget>

class CDimmer;

class PDimmer : public QGraphicsProxyWidget {
public:
    PDimmer(CDimmer*, int min, int max, int defaultValue, QGraphicsItem* parent = 0);
};

#endif // PDIMMER_H
