#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QGraphicsWidget>

class PixmapWidget : public QGraphicsWidget {
    Q_OBJECT

public:
    PixmapWidget(QString filename, bool showClickable, QGraphicsItem* parent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

signals:
    void clicked();

private:
    QGraphicsPixmapItem m_pixmapItem;
    bool m_showClickable;
};

#endif // PIXMAPWIDGET_H
