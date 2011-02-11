#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QGraphicsWidget>

class PixmapWidget : public QGraphicsWidget {
public:
    PixmapWidget(QString filename, QGraphicsItem* parent);

private:
    QGraphicsPixmapItem m_pixmapItem;
};

#endif // PIXMAPWIDGET_H
