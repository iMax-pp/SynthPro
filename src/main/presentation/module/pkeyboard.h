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
    explicit PKeyboard(CKeyboard*);

    void initialize(PVirtualPort* outputFrequency, PVirtualPort* outputGate);

    /**
     * Needed to be called after the addition in the scene, as grabKeyboard() needs it.
     */
    void postInitialize();

private slots:
    /**
     * Indicate to the Controller a key has been pressed.
     */
    void keyboardKeyPressed(int keyPressed);

    /**
     * Indicate to the Controller a key has been released.
     */
    void keyboardKeyReleased(int keyPressed);

private:
    PKeyboardView* m_pKeyboardView;
};

#endif // PKEYBOARD_H
