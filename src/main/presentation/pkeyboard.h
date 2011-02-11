#ifndef PKEYBOARD_H
#define PKEYBOARD_H

#include "presentation/pmodule.h"

class Buffer;
class CKeyboard;
class PKeyboardView;
class PVirtualPort;

class PKeyboard : public PModule {
    Q_OBJECT

public:
    PKeyboard(CKeyboard*);

    void initialize(PVirtualPort* outputFrequency, PVirtualPort* outputGate);

private slots:
    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);

private:
    PKeyboardView* m_pKeyboardView;
};

#endif // PKEYBOARD_H
