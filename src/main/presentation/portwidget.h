#ifndef PORTWIDGET_H
#define PORTWIDGET_H

#include <QGraphicsWidget>

class CPortWidget;
class PPort;

/**
 * Represents a single port in a PPort widget
 */
class PortWidget : public QGraphicsWidget {
public:
    PortWidget(CPortWidget* control, PPort* parent);
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    inline CPortWidget* control() const { return m_control; }

    static const int PORT_SIZE = 15;

protected:
    // Handle drag & drop events
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    CPortWidget* m_control;
};

#endif // PORTWIDGET_H
