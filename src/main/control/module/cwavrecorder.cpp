#include "cwavrecorder.h"

#include "control/component/cinport.h"
#include "control/component/cpushbutton.h"
#include "presentation/module/pwavrecorder.h"

CWavRecorder::CWavRecorder(SynthPro* parent, int nbProcessingBeforeSaving)
    : Module(parent)
    , WavRecorder(parent, nbProcessingBeforeSaving)
    , CModule(parent)
{
}

void CWavRecorder::initialize(SynthProFactory* factory, bool loadFile)
{
    WavRecorder::initialize(factory);

    CInPort* inPort = dynamic_cast<CInPort*>(m_inPort);
    CPushButton* recordButton = dynamic_cast<CPushButton*>(m_recordButton);
    CPushButton* stopButton = dynamic_cast<CPushButton*>(m_stopButton);

    PWavRecorder* pre = dynamic_cast<PWavRecorder*>(presentation());
    pre->initialize(inPort->presentation(), recordButton->presentation(), stopButton->presentation());

    connect(pre, SIGNAL(newFileClicked()), this, SLOT(newFile()));

    if (loadFile) {
        newFile();
    }
}

void CWavRecorder::newFile()
{
    QString fileName = dynamic_cast<PWavRecorder*>(presentation())->askForFileName();
    if (!fileName.isNull()) {
        WavRecorder::newFile(fileName);
    }
}

QString CWavRecorder::settings() const
{
    return m_fileName;
}

void CWavRecorder::setUpSettings(const QString& settings)
{
    QStringList list = settings.split(" ", QString::SkipEmptyParts);

    WavRecorder::newFile(list[0]);
}
