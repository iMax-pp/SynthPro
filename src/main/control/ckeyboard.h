#ifndef CKEYBOARD_H
#define CKEYBOARD_H

#include "abstraction/modulekeyboard.h"
#include "control/cmodule.h"

class CKeyboard : public ModuleKeyboard, public CModule {

public:
    explicit CKeyboard(SynthPro*);

    void initialize(SynthProFactory*);

    /**
      * Process the input signal.
      */
    virtual void ownProcess();

    void keyboardKeyPressed(int keyPressed);
    void keyboardKeyReleased(int keyPressed);
};

#endif // CKEYBOARD_H
