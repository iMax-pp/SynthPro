#ifndef POSCILLOSCOPEVIEW_H
#define POSCILLOSCOPEVIEW_H

#include "abstraction/buffer.h"
#include <QGraphicsWidget>

class POscilloscopeView : public QGraphicsWidget {
public:
    POscilloscopeView(QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    // Useful ??
    // inline VOscilloscopeView control() const { return m_control; }

    static const int WIDTH = 200;
    static const int HEIGHT = 150;

private:
    // COscilloscopeView m_control;
    qreal* m_inBuffer; // FIXME : Try. Stashed here for the moment.
    static const qreal STEP = Buffer::DEFAULT_LENGTH / WIDTH;
    qreal m_ratioY;
};

#endif // POSCILLOSCOPEVIEW_H
