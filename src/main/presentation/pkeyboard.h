#ifndef PKEYBOARD_H
#define PKEYBOARD_H

#include "presentation/pmodule.h"

class Buffer;
class CKeyboard;
class PVirtualPort;

class PKeyboard : public PModule {

public:
    PKeyboard(CKeyboard*);

    void initialize(PVirtualPort* outputFrequency, PVirtualPort* outputGate);
};

#endif // PKEYBOARD_H
