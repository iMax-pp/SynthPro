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

    inline PPort* parentPort() const { return m_parent; }

    static const int PORT_SIZE = 15;
private:
    PPort* m_parent;
};

#endif // PORTWIDGET_H
