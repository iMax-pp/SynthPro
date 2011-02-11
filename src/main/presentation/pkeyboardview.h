#ifndef PKEYBOARDVIEW_H
#define PKEYBOARDVIEW_H

#include "presentation/pkeyboardkey.h"
#include <QGraphicsWidget>

class PKeyboardView : public QGraphicsWidget {
    Q_OBJECT

public:
    PKeyboardView(QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    static const int NB_OCTAVES = 3;
    static const int NB_WHITE_KEYS_PER_OCTAVE = 7;
    static const int FIRST_KEY_NUMBER = (NB_OCTAVES / 2) * -12;

    static const int WIDTH = PKeyboardKey::WHITE_KEY_WIDTH * NB_OCTAVES * NB_WHITE_KEYS_PER_OCTAVE;
    static const int HEIGHT = PKeyboardKey::WHITE_KEY_HEIGHT;

signals:
    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);
};

#endif // PKEYBOARDVIEW_H
