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

    connect(pre, SIGNAL(newFileClicked()), this, SLOT(newFile()));
    connect(pre, SIGNAL(startRecordingClicked()), this, SLOT(startRecording()));
    connect(pre, SIGNAL(stopRecordingClicked()), this, SLOT(stopRecording()));

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
