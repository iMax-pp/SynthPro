#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QGraphicsWidget>

/**
 * Widget only class (no PAC involved), for a Pixmap.
 */
class PixmapWidget : public QGraphicsWidget {
    Q_OBJECT

public:
    PixmapWidget(QString filename, QGraphicsItem* parent);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*);

signals:
    void clicked();

private:
    QGraphicsPixmapItem m_pixmapItem;
};

#endif // PIXMAPWIDGET_H
