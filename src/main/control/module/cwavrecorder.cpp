#include "cwavrecorder.h"

#include "control/component/cinport.h"
#include "presentation/module/pwavrecorder.h"

CWavRecorder::CWavRecorder(SynthPro* parent, int nbProcessingBeforeSaving)
    : Module(parent)
    , WavRecorder(parent, nbProcessingBeforeSaving)
    , CModule(parent)
{
}

void CWavRecorder::initialize(SynthProFactory* factory)
{
    WavRecorder::initialize(factory);

    CInPort* inPort = dynamic_cast<CInPort*>(m_inPort);

    PWavRecorder* pre = dynamic_cast<PWavRecorder*>(presentation());
    pre->initialize(inPort->presentation());
    connect(pre, SIGNAL(askNewFile()), this, SLOT(startNewFile()));
    connect(pre, SIGNAL(stopRecording()), this, SLOT(stopRecording()));

    startNewFile();
}

void CWavRecorder::startNewFile()
{
    QString fileName = dynamic_cast<PWavRecorder*>(presentation())->askForFileName();
    if (!fileName.isNull()) {
        WavRecorder::startNewFile(fileName);
    }
}

void CWavRecorder::stopRecording()
{
    closeWAVFile();
}
