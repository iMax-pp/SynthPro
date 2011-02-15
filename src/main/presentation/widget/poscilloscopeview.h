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

    static const int BUFFER_INVISIBLE = 250;

    static const qreal RATIO_Y_MIN = 0.2;
    static const qreal RATIO_Y_MAX = 2.0;
    static const qreal RATIO_Y_DEFAULT = 0.5;

private:
    Buffer* m_inBuffer;
    qreal m_ratioY;
    bool m_stabilized;
};

#endif // POSCILLOSCOPEVIEW_H
