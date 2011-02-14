#include "cmixer.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "presentation/component/pport.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/module/pmixer.h"


#include <QMap>

CMixer::CMixer(SynthPro* parent)
    : Module(parent)
    , Mixer(parent)
    , CModule(parent)
{
}

void CMixer::initialize(SynthProFactory* factory )
{
    Mixer::initialize(factory);

    QMap<InPort*, Dimmer*>::iterator ite;
    QMap<PVirtualPort*, PDimmer*>* pMixerMap = new QMap<PVirtualPort*, PDimmer*>();

    for (ite = m_MixInPorts->begin() ; ite != m_MixInPorts->end() ; ite++) {
        pMixerMap->insert(
                dynamic_cast<CInPort*>(ite.key())->presentation(),
                dynamic_cast<CDimmer*>(ite.value())->presentation());
    }

    COutPort* out = dynamic_cast<COutPort*>(m_outPort);

    dynamic_cast<PMixer*>(presentation())->initialize(pMixerMap, out->presentation());
}
