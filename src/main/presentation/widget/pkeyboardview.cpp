#include "pkeyboardview.h"

#include <QMap>
#include <QPainter>

PKeyboardView::PKeyboardView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
{
    setMinimumSize(boundingRect().size()); 
}

// This method is post-initialized because it requires to use "grabKeyboard()" in order
// to use the keyboard shortcuts. But it can only be done after its parent has been
// added to its scene.
void PKeyboardView::postInitialize()
{
    grabKeyboard();

    // Temporary map to link a virtual key to a computer keyboard key.
    QMap<int, int> mapKeyNumberToKey;
    int k = FIRST_KEY_NUMBER_ASSIGNED_TO_KEYBOARD;
    mapKeyNumberToKey.insert(k++, Qt::Key_Q);
    mapKeyNumberToKey.insert(k++, Qt::Key_Z);
    mapKeyNumberToKey.insert(k++, Qt::Key_S);
    mapKeyNumberToKey.insert(k++, Qt::Key_E);
    mapKeyNumberToKey.insert(k++, Qt::Key_D);
    mapKeyNumberToKey.insert(k++, Qt::Key_F);
    mapKeyNumberToKey.insert(k++, Qt::Key_T);
    mapKeyNumberToKey.insert(k++, Qt::Key_G);
    mapKeyNumberToKey.insert(k++, Qt::Key_Y);
    mapKeyNumberToKey.insert(k++, Qt::Key_H);
    mapKeyNumberToKey.insert(k++, Qt::Key_U);
    mapKeyNumberToKey.insert(k++, Qt::Key_J);
    mapKeyNumberToKey.insert(k++, Qt::Key_K);

    // Create the keyboard keys.
    int x = 0;
    int keyNumber = FIRST_KEY_NUMBER;
    for (int i = 0; i < NB_OCTAVES; i++) {
        for (int k = 0 ; k < NB_WHITE_KEYS_PER_OCTAVE; k++) {
            // Adding the white keys.
            PKeyboardKey* whiteKey = new PKeyboardKey(this, keyNumber, true);
            // Linking the key to a computer keyboard key.
            if (mapKeyNumberToKey.contains(keyNumber)) {
                m_mapKeyToKeyPointer.insert(mapKeyNumberToKey.value(keyNumber), whiteKey);
            }
            // Get the signal from the keys.
            connect(whiteKey, SIGNAL(keyboardKeyPressed(int)), this, SIGNAL(keyboardKeyPressed(int)));
            connect(whiteKey, SIGNAL(keyboardKeyReleased(int)), this, SIGNAL(keyboardKeyReleased(int)));
            whiteKey->setPos(x, 0);
            keyNumber++;

            // Adding the black keys.
            if ((k != 2) && (k != 6)) {
                PKeyboardKey* blackKey = new PKeyboardKey(this, keyNumber, false);
                // Linking the key to a computer keyboard key.
                if (mapKeyNumberToKey.contains(keyNumber)) {
                    m_mapKeyToKeyPointer.insert(mapKeyNumberToKey.value(keyNumber), blackKey);
                }
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

void PKeyboardView::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if (m_mapKeyToKeyPointer.contains(key)) {
        PKeyboardKey* keyboardKey = m_mapKeyToKeyPointer.value(key);
        keyboardKey->keyPressed();
    }
}

void PKeyboardView::keyReleaseEvent(QKeyEvent* event)
{
    int key = event->key();
    if (m_mapKeyToKeyPointer.contains(key)) {
        PKeyboardKey* keyboardKey = m_mapKeyToKeyPointer.value(key);
        keyboardKey->keyReleased();
    }
}
