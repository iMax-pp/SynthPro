#ifndef PIXMAPBUTTONWIDGET_H
#define PIXMAPBUTTONWIDGET_H

#include "presentation/widget/pixmapwidget.h"

/**
 * Widget only class (no PAC involved), for a clickable PixmapWidget.
 */
class PixmapButtonWidget : public PixmapWidget {
public:
    PixmapButtonWidget(const QString& fileName, QGraphicsItem* parent);

    /// @returns A boolean indicating if the PixmapButtonWidget is activated.
    inline bool activated() const { return m_activated; }
    /// Set the PixmapButtonWidget to activated (or deactivated).
    void setActivated(bool);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    bool m_activated;
    QPointF m_originPos;
};

#endif // PIXMAPBUTTONWIDGET_H
