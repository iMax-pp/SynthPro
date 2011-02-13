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

    connect(pre, SIGNAL(askNewFile()), this, SLOT(newFile()));
    connect(pre, SIGNAL(startRecording()), this, SLOT(startRecording()));
    connect(pre, SIGNAL(stopRecording()), this, SLOT(stopRecording()));

    newFile();
}

void CWavRecorder::newFile()
{
    QString fileName = dynamic_cast<PWavRecorder*>(presentation())->askForFileName();
    if (!fileName.isNull()) {
        WavRecorder::newFile(fileName);
    }
}

void CWavRecorder::startRecording()
{
    WavRecorder::startRecording();
}

void CWavRecorder::stopRecording()
{
    WavRecorder::stopRecording();
}
