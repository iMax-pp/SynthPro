#ifndef CKEYBOARD_H
#define CKEYBOARD_H

#include "abstraction/module/keyboard.h"
#include "control/cmodule.h"

class CKeyboard : public Keyboard, public CModule {

public:
    explicit CKeyboard(SynthPro*);

    void initialize(SynthProFactory*);

    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);
};

#endif // CKEYBOARD_H
