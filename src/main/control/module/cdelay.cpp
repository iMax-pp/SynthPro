#include "cdelay.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "presentation/module/pdelay.h"

#include <QTextStream>

CDelay::CDelay(SynthPro* parent)
    : Module(parent)
    , Delay(parent)
    , CModule(parent)
{
}

void CDelay::initialize(SynthProFactory* factory)
{
    Delay::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);
    COutPort* out = dynamic_cast<COutPort*>(m_outPort);
    CDimmer* duration = dynamic_cast<CDimmer*>(m_durationDimmer);
    CDimmer* decay = dynamic_cast<CDimmer*>(m_decayDimmer);

    duration->setValueFormat(CDimmer::timeFormat);
    decay->setValueFormat(CDimmer::percentageFormat);

    dynamic_cast<PDelay*>(presentation())->initialize(in->presentation(), out->presentation(),
                                                      duration->presentation(), decay->presentation());
}

QString CDelay::settings() const
{
    QString result;
    QTextStream(&result) << m_durationDimmer->value() << " "
                         << m_decayDimmer->value();

    return result;
}

void CDelay::setUpSettings(const QString& settings)
{
    QStringList list = settings.split(" ", QString::SkipEmptyParts);

    m_durationDimmer->setValue(list[0].toFloat());
    m_decayDimmer->setValue(list[1].toFloat());
}
