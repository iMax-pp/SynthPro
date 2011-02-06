#ifndef PMODULE_H
#define PMODULE_H

#include <QGraphicsRectItem>

class PModule : public QGraphicsRectItem {
public:
    PModule();

protected:
    static const qreal DEFAULT_WIDTH = 150;
    static const qreal DEFAULT_HEIGHT = 100;
};

#endif // PMODULE_H
