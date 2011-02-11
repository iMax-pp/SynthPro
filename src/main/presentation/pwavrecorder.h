#ifndef PWAVRECORDER_H
#define PWAVRECORDER_H

#include "presentation/pmodule.h"

class CWavRecorder;
class PVirtualPort;

class PWavRecorder : public PModule {
public:
    explicit PWavRecorder(CWavRecorder*);
    
    void initialize(PVirtualPort* in);
};

#endif // PWAVRECORDER_H
