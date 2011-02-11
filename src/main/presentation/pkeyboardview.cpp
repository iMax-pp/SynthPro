#include "pkeyboardview.h"

#include "pkeyboardkey.h"

#include <QPainter>

PKeyboardView::PKeyboardView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
{
    setMinimumSize(boundingRect().size());

    // Create the keyboard keys.
    int x = 0;
    int keyNumber = FIRST_KEY_NUMBER;
    for (int i = 0; i < NB_OCTAVES; i++) {
        for (int k = 0 ; k < NB_WHITE_KEYS_PER_OCTAVE; k++) {
            // Adding the white keys.
            PKeyboardKey* whiteKey = new PKeyboardKey(this, keyNumber, true);
            // Get the signal from the keys.
            connect(whiteKey, SIGNAL(keyboardKeyPressed(int)), this, SIGNAL(keyboardKeyPressed(int)));
            connect(whiteKey, SIGNAL(keyboardKeyReleased(int)), this, SIGNAL(keyboardKeyReleased(int)));
            whiteKey->setPos(x, 0);
            keyNumber++;

            // Adding the black keys.
            if ((k != 2) && (k != 6)) {
                PKeyboardKey* blackKey = new PKeyboardKey(this, keyNumber, false);
                // Get the signal from the keys.
                connect(blackKey, SIGNAL(keyboardKeyPressed(int)), this, SIGNAL(keyboardKeyPressed(int)));
                connect(blackKey, SIGNAL(keyboardKeyReleased(int)), this, SIGNAL(keyboardKeyReleased(int)));
                blackKey->setPos(x + (PKeyboardKey::WHITE_KEY_WIDTH * 2 - PKeyboardKey::BLACK_KEY_WIDTH) / 2, 0);
                blackKey->setZValue(1);
                keyNumber++;
            }

            x += PKeyboardKey::WHITE_KEY_WIDTH;
        }
    }
}

void PKeyboardView::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
}

QRectF PKeyboardView::boundingRect() const
{
    return QRectF(-5, -5, WIDTH + 10, HEIGHT + 10);
}
