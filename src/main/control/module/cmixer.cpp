#include "cmixer.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "presentation/component/pport.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/module/pmixer.h"

#include <QMap>
#include <QTextStream>

CMixer::CMixer(SynthPro* parent)
    : Module(parent)
    , Mixer(parent)
    , CModule(parent)
{
}

void CMixer::initialize(SynthProFactory* factory)
{
    Mixer::initialize(factory);

    QMap<InPort*, Dimmer*>::iterator it;
    QMap<PVirtualPort*, PDimmer*> pMixerMap;

    for (it = m_mixInPorts->begin(); it != m_mixInPorts->end(); it++) {
        CDimmer* dimmer = dynamic_cast<CDimmer*>(it.value());
        dimmer->setValueFormat(CDimmer::percentageFormat);
        pMixerMap.insert(
                dynamic_cast<CInPort*>(it.key())->presentation(),
                dimmer->presentation());
    }

    COutPort* out = dynamic_cast<COutPort*>(m_outPort);

    dynamic_cast<PMixer*>(presentation())->initialize(pMixerMap, out->presentation());
}

QString CMixer::settings() const
{
    QString result;
    QTextStream stream(&result);
    QMap<InPort*, Dimmer*>::iterator it;

    for (it = m_mixInPorts->begin(); it != m_mixInPorts->end(); it++) {
        stream << it.value()->value() << " ";
    }

    return result;
}

void CMixer::setUpSettings(const QString& settings)
{
    QStringList list = settings.split(" ", QString::SkipEmptyParts);
    QMap<InPort*, Dimmer*>::iterator it;

    int i = 0;
    for (it = m_mixInPorts->begin(); it != m_mixInPorts->end(); it++) {
        it.value()->setValue(list[i].toFloat());
        i++;
    }
}
