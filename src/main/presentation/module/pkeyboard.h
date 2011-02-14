#ifndef PKEYBOARD_H
#define PKEYBOARD_H

#include "presentation/pmodule.h"

#include <QMap>

class Buffer;
class CKeyboard;
class PKeyboardView;
class PVirtualPort;

class PKeyboard : public PModule {
    Q_OBJECT

public:
    PKeyboard(CKeyboard*);

    void initialize(PVirtualPort* outputFrequency, PVirtualPort* outputGate);

    /**
      * Needed to be called after the addition in the scene, as grabKeyboard() needs it.
      */
    void postInitialize();

    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

private slots:
    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);

private:
    PKeyboardView* m_pKeyboardView;
    QMap<int, int>* m_mapKeyboard;
};

#endif // PKEYBOARD_H
