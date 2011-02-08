#ifndef PCHANNEL_H
#define PCHANNEL_H

#include <QGraphicsLineItem>

class CChannel;

class PChannel : public QGraphicsLineItem {
public:
    PChannel(CChannel*, QGraphicsScene*);

    QRectF boundingRect() const;

public slots:
    void updatePosition(QPointF);

private:
    CChannel* m_control;
};

#endif // PCHANNEL_H
