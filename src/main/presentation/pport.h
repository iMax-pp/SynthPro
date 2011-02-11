#ifndef PPORT_H
#define PPORT_H

#include <QGraphicsWidget>

class CPort;
class PVirtualPort;

/**
 * Represents a single port in a PPort widget
 */
class PPort : public QGraphicsWidget {
public:
    PPort(CPort* control, QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    inline CPort* control() const { return m_control; }

    static const int PORT_SIZE = 15;

    void showFeedback(bool compatible);
    void hideFeedback();

protected:
    // Handle drag & drop events
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    CPort* m_control;
};

#endif // PPORT_H
