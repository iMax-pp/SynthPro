#include "csampler.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cpushbutton.h"
#include "presentation/module/psampler.h"

#include <QTextStream>

CSampler::CSampler(SynthPro* parent)
    : Module(parent)
    , Sampler(parent)
    , CModule(parent)
{
}

void CSampler::initialize(SynthProFactory* factory)
{
    Sampler::initialize(factory);

    CInPort* inPort = dynamic_cast<CInPort*>(m_inPort);
    COutPort* outPort = dynamic_cast<COutPort*>(m_outPort);
    CInPort* gate = dynamic_cast<CInPort*>(m_gate);
    CDimmer* bpmDimmer = dynamic_cast<CDimmer*>(m_bpmDimmer);
    CPushButton* record = dynamic_cast<CPushButton*>(m_recordButton);
    CPushButton* stop = dynamic_cast<CPushButton*>(m_stopButton);
    CPushButton* play = dynamic_cast<CPushButton*>(m_playButton);

    bpmDimmer->setValueFormat(formatSpeed);

    PSampler* pre = dynamic_cast<PSampler*>(presentation());
    pre->initialize(inPort->presentation(), outPort->presentation(),
                    gate->presentation(), bpmDimmer->presentation(),
                    record->presentation(), stop->presentation(), play->presentation());

    connect(this, SIGNAL(valueChanged(int)), pre, SIGNAL(valueChanged(int)));
    connect(this, SIGNAL(lengthChanged(int)), pre, SIGNAL(lengthChanged(int)));
}

QString CSampler::formatSpeed(qreal value)
{
    return QString::number(value, 'g', 2) + "x";
}

QString CSampler::settings() const
{
    QString result;
    QTextStream(&result) << m_bpmDimmer->value();

    return result;
}

void CSampler::setUpSettings(const QString& settings)
{
    QStringList list = settings.split(" ", QString::SkipEmptyParts);

    m_bpmDimmer->setValue(list[0].toFloat());
}
