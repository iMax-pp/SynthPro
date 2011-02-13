#ifndef PIXMAPBUTTONWIDGET_H
#define PIXMAPBUTTONWIDGET_H

#include "presentation/widget/pixmapwidget.h"

class PixmapButtonWidget : public PixmapWidget {
public:
    PixmapButtonWidget(const QString& fileName, QGraphicsItem* parent);

    inline bool activated() const { return m_activated; }
    void setActivated(bool);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    bool m_activated;
    QPointF m_originPos;
};

#endif // PIXMAPBUTTONWIDGET_H
