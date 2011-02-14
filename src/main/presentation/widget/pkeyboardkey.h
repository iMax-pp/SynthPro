#ifndef PKEYBOARDKEY_H
#define PKEYBOARDKEY_H

class QBrush;

#include <QGraphicsWidget>

class PKeyboardKey : public QGraphicsWidget {
    Q_OBJECT

public:
    PKeyboardKey(QGraphicsItem* parent, int keyNumber, bool whiteKey, bool assignKey);
    virtual ~PKeyboardKey();

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    static const int WHITE_KEY_WIDTH = 16;
    static const int WHITE_KEY_HEIGHT = 50;

    static const int BLACK_KEY_WIDTH = 10;
    static const int BLACK_KEY_HEIGHT = 30;

signals:
    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);

private:
    int m_keyNumber; // Relative to the C4.
    int m_width;
    int m_height;
    bool m_pressed;
    QBrush* m_fillKeyBrush;
    QBrush* m_fillKeyBrushPressed;
    // static QList<char> m_keys;
};

#endif // PKEYBOARDKEY_H
