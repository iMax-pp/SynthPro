#ifndef PVIRTUALPORT_H
#define PVIRTUALPORT_H

#include <QGraphicsWidget>

class CVirtualPort;
class TextWidget;
class PPort;
class QGraphicsLinearLayout;

class PVirtualPort : public QGraphicsWidget {
public:
    PVirtualPort(CVirtualPort*, QGraphicsItem* parent);
    void initialize(PPort* availablePort);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    inline CVirtualPort* control() const { return m_control; }

    void addConnectionPort(PPort*);
    void removeConnectionPort(PPort*);

private:
    CVirtualPort* m_control;
    TextWidget* m_label;
    QGraphicsLinearLayout* m_connectionsLayout;
    QGraphicsLinearLayout* m_portsLayout;
};

#endif // PVIRTUALPORT_H
