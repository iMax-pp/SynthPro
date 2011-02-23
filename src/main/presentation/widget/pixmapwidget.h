#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QGraphicsWidget>

/**
 * Widget only class (no PAC involved), for a Pixmap.
 */
class PixmapWidget : public QGraphicsWidget {
    Q_OBJECT

public:
    PixmapWidget(const QString& filename, QGraphicsItem* parent);
    PixmapWidget(const QPixmap& filename, QGraphicsItem* parent);

    void setPixmap(const QPixmap& filename);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*);

signals:
    void clicked();

private:
    QGraphicsPixmapItem m_pixmapItem;
};

#endif // PIXMAPWIDGET_H
