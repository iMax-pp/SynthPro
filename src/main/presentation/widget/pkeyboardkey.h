#ifndef PKEYBOARDKEY_H
#define PKEYBOARDKEY_H

class QBrush;

#include <QGraphicsWidget>

/**
 * Widget only class (no PAC involved), representing a key on the Keyboard.
 */
class PKeyboardKey : public QGraphicsWidget {
    Q_OBJECT

public:
    PKeyboardKey(QGraphicsItem* parent, int keyNumber, bool whiteKey /*, int keyAssigned = 0*/);
    virtual ~PKeyboardKey();

    /// Overriden method to draw the Key.
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    /// Overriden method returning the shape of the Key.
    QRectF boundingRect() const;

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

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    int m_keyNumber; // Relative to the C4.
    int m_width;
    int m_height;
    bool m_pressed;
    QBrush* m_fillKeyBrush;
    QBrush* m_fillKeyBrushPressed;
};

#endif // PKEYBOARDKEY_H
