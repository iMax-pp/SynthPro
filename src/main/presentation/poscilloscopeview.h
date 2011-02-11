#ifndef POSCILLOSCOPEVIEW_H
#define POSCILLOSCOPEVIEW_H

#include "abstraction/buffer.h"
#include <QGraphicsWidget>

class POscilloscopeView : public QGraphicsWidget {
public:
    POscilloscopeView(QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    /**
      * Define the buffer to be visualized.
      */
    void setVisualizedBuffer(Buffer*);

    static const int WIDTH = 200;
    static const int HEIGHT = 150;

private:
    Buffer* m_inBuffer;
    qreal m_ratioY;
};

#endif // POSCILLOSCOPEVIEW_H
