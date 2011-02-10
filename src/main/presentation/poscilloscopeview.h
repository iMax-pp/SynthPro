#ifndef POSCILLOSCOPEVIEW_H
#define POSCILLOSCOPEVIEW_H

#include <QGraphicsWidget>

class POscilloscopeView : public QGraphicsWidget
{
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
    static const int BUFFER_SIZE = 900; // TODO : from VCO.
    static const qreal STEP = BUFFER_SIZE / WIDTH;
    qreal m_ratioY;
};

#endif // POSCILLOSCOPEVIEW_H
