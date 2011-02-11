#ifndef PKEYBOARDKEY_H
#define PKEYBOARDKEY_H

class QBrush;

#include <QGraphicsWidget>

class PKeyboardKey : public QGraphicsWidget {

public:
    PKeyboardKey(QGraphicsItem* parent, bool whiteKey);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    static const int WHITE_KEY_WIDTH = 16;
    static const int WHITE_KEY_HEIGHT = 50;

    static const int BLACK_KEY_WIDTH = 10;
    static const int BLACK_KEY_HEIGHT = 30;

private:
    int m_width;
    int m_height;
    QBrush* m_fillKeyBrush;
};

#endif // PKEYBOARDKEY_H
