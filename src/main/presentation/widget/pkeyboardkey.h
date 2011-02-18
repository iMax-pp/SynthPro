#ifndef PKEYBOARDKEY_H
#define PKEYBOARDKEY_H

class QBrush;

#include <QGraphicsWidget>

class PKeyboardKey : public QGraphicsWidget {
    Q_OBJECT

public:
    PKeyboardKey(QGraphicsItem* parent, int keyNumber, bool whiteKey /*, int keyAssigned = 0*/);
    virtual ~PKeyboardKey();

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    /**
      * Behaviour to perform when the key is pressed.
      * Triggered by the mouse event, but also by the View (through the computer keyboard).
      */
    void keyPressed();

    /**
      * Behaviour to perform when the key is released.
      * Triggered by the mouse event, but also by the View (through the computer keyboard).
      */
    void keyReleased();

    static const int WHITE_KEY_WIDTH = 16;
    static const int WHITE_KEY_HEIGHT = 50;

    static const int BLACK_KEY_WIDTH = 10;
    static const int BLACK_KEY_HEIGHT = 30;

signals:
    /**
     * Signal emitted when a Keyboard Key is pressed.
     */
    void keyboardKeyPressed(int keyPressed);

    /**
     * Signal emitted when a Keyboard Key is released.
     */
    void keyboardKeyReleased(int keyPressed);

private:
    int m_keyNumber; // Relative to the C4.
    int m_width;
    int m_height;
    bool m_pressed;
    QBrush* m_fillKeyBrush;
    QBrush* m_fillKeyBrushPressed;
};

#endif // PKEYBOARDKEY_H
