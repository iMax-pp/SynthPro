#ifndef CKEYBOARD_H
#define CKEYBOARD_H

#include "abstraction/module/keyboard.h"
#include "control/cmodule.h"

/**
 * Keyboard control class (PAC by inheritance).
 */
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

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);
};

#endif // CKEYBOARD_H
