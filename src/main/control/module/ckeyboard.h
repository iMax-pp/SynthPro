#ifndef CKEYBOARD_H
#define CKEYBOARD_H

#include "abstraction/module/keyboard.h"
#include "control/cmodule.h"

class CKeyboard : public Keyboard, public CModule {

public:
    explicit CKeyboard(SynthPro*);

    void initialize(SynthProFactory*);

    /**
      * Useful to the Presentation of the module.
      */
    void postInitialize();

    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);
};

#endif // CKEYBOARD_H
