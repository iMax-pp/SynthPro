#ifndef PKEYBOARDVIEW_H
#define PKEYBOARDVIEW_H

#include "presentation/widget/pkeyboardkey.h"

#include <QDebug>
#include <QGraphicsWidget>
#include <QMap>

class PKeyboardKey;

/**
 * Widget only class (no PAC involved), representing a Keyboard.
 */
class PKeyboardView : public QGraphicsWidget {
    Q_OBJECT

public:
    explicit PKeyboardView(QGraphicsItem* parent);

    void postInitialize();

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    static const int NB_OCTAVES = 3;
    static const int NB_WHITE_KEYS_PER_OCTAVE = 7;
    static const int FIRST_KEY_NUMBER = (NB_OCTAVES / 2) * -12;
    static const int FIRST_KEY_NUMBER_ASSIGNED_TO_KEYBOARD = FIRST_KEY_NUMBER + 12;

    static const int WIDTH = PKeyboardKey::WHITE_KEY_WIDTH * NB_OCTAVES * NB_WHITE_KEYS_PER_OCTAVE;
    static const int HEIGHT = PKeyboardKey::WHITE_KEY_HEIGHT;

signals:
    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);

protected:
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

private:
    QMap<int, PKeyboardKey*> m_mapKeyToKeyPointer;
};

#endif // PKEYBOARDVIEW_H
