#ifndef PPORT_H
#define PPORT_H

#include <QGraphicsEllipseItem>

class CPort;

class PPort : public QGraphicsEllipseItem {
public:
    PPort(CPort*, QGraphicsItem* parent);

    CPort* control() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    CPort* m_control;
};

#endif // PPORT_H
