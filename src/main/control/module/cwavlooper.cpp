#include "cwavlooper.h"

#include "control/component/cdimmer.h"
#include "control/component/coutport.h"
#include "presentation/module/pwavlooper.h"

#include <QTextStream>

CWavLooper::CWavLooper(SynthPro* parent)
    : Module(parent)
    , WavLooper(parent)
    , CModule(parent)
{
}

void CWavLooper::initialize(SynthProFactory* factory, bool loadFile)
{
    WavLooper::initialize(factory);

    COutPort* outPort = dynamic_cast<COutPort*>(m_outPort);
    CDimmer* speedDimmer = dynamic_cast<CDimmer*>(m_sDimmer);
    PWavLooper* pre = dynamic_cast<PWavLooper*>(presentation());
    pre->initialize(outPort->presentation(), speedDimmer->presentation());

    speedDimmer->setValueFormat(formatSpeed);

    connect(pre, SIGNAL(newFileClicked()), this, SLOT(newFile()));

    if (loadFile) {
        newFile();
    }
}

QString CWavLooper::settings() const
{
    QString result;
    QTextStream(&result) << m_sDimmer->value() << " " << m_fileName;

    return result;
}

void CWavLooper::setUpSettings(const QString& settings)
{
    QStringList list = settings.split(" ", QString::SkipEmptyParts);

    m_sDimmer->setValue(list[0].toFloat());
    WavLooper::newFile(list[1]);
}

void CWavLooper::newFile()
{
    QString fileName = dynamic_cast<PWavLooper*>(presentation())->askForFileName();
    if (!fileName.isNull()) {
        WavLooper::newFile(fileName);
    }
}

QString CWavLooper::formatSpeed(qreal val)
{
    return QString::number(val, 'g', 2) + "x";
}
