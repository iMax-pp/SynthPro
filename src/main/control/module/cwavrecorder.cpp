#include "cwavrecorder.h"

#include "control/component/cinport.h"
#include "presentation/module/pwavrecorder.h"

CWavRecorder::CWavRecorder(SynthPro* parent, QString fileName, int nbProcessingBeforeSaving)
    : Module(parent)
    , WavRecorder(parent, fileName, nbProcessingBeforeSaving)
    , CModule(parent)
{
}

void CWavRecorder::initialize(SynthProFactory* factory)
{
    WavRecorder::initialize(factory);
    
    CInPort* inPort = dynamic_cast<CInPort*>(m_inPort);
    
    dynamic_cast<PWavRecorder*>(presentation())->initialize(inPort->presentation());
}
