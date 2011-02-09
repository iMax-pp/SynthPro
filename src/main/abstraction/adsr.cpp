#include "adsr.h"


#include "factory/synthprofactory.h"


ADSR::ADSR(QObject* parent)
    : Module(parent)
{
}

void ADSR::initialize(SynthProFactory* factory)
{
    m_gate = factory->createInPortGate(this, "gate");
    m_inports.append(m_gate);

    m_outPort = factory->createOutPortReplicable(this, "outPort");
    m_outports.append(m_outPort);

    m_attackDimmer = factory->createDimmer(ATTACK_MIN, ATTACK_MAX, ATTACK_DEFAULT, this);
    m_decayDimmer = factory->createDimmer(DECAY_MIN, DECAY_MAX, DECAY_DEFAULT, this);
    m_sustainDimmer = factory->createDimmer(SUSTAIN_MIN, SUSTAIN_MAX, SUSTAIN_DEFAULT, this);
    m_releaseDimmer = factory->createDimmer(RELEASE_MIN, RELEASE_MAX, RELEASE_DEFAULT, this);

}

void ADSR::ownProcess()
{

}
