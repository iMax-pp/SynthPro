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

    /**
     * Called by the Presentation to indicates a key has been pressed.
     */
    void keyboardKeyPressed(int keyPressed);

    /**
     * Called by the Presentation to indicates a key has been released.
     */
    void keyboardKeyReleased(int keyPressed);
};

#endif // CKEYBOARD_H
