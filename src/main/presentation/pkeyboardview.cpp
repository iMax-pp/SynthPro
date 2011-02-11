#include "pkeyboardview.h"

#include "pkeyboardkey.h"

#include <QPainter>

PKeyboardView::PKeyboardView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
{
    setMinimumSize(boundingRect().size());

    // Create the keyboard keys.
    int x = 0;
    for (int i = 0; i < NB_OCTAVES; i++) {
        // Adding the white keys.
        for (int k = 0 ; k < NB_WHITE_KEYS_PER_OCTAVE; k++) {
            PKeyboardKey* whiteKey = new PKeyboardKey(this, true);
            whiteKey->setPos(x, 0);

            // Adding the black keys.
            if ((k != 2) && (k != 6)) {
                PKeyboardKey* blackKey = new PKeyboardKey(this, false);
                blackKey->setPos(x + (PKeyboardKey::WHITE_KEY_WIDTH * 2 - PKeyboardKey::BLACK_KEY_WIDTH) / 2, 0);
                blackKey->setZValue(1);
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
