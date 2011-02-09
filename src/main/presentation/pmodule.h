#ifndef PMODULE_H
#define PMODULE_H

#include <QGraphicsWidget>

class CModule;

class PModule : public QGraphicsWidget {
public:
    PModule(CModule*);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

protected:
    /*
     * Intercept mouse moving to update the hooked wires accordingly.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);


    CModule* m_control;
    static const qreal DEFAULT_WIDTH = 150;
    static const qreal DEFAULT_HEIGHT = 100;
};

#endif // PMODULE_H
