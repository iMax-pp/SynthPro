#ifndef PORTWIDGET_H
#define PORTWIDGET_H

#include <QGraphicsWidget>

class PPort;

/**
 * Represents a single port in a PPort widget
 */
class PortWidget : public QGraphicsWidget {
public:
    PortWidget(PPort* parent);
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    static const int PORT_SIZE = 15;

};

#endif // PORTWIDGET_H
