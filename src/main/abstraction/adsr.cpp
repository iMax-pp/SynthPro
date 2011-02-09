#include "adsr.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/dimmer.h"
#include "abstraction/outport.h"
#include "factory/synthprofactory.h"

ADSR::ADSR(QObject* parent)
    : Module(parent)
    , m_timeLine(0)
{
}

void ADSR::initialize(SynthProFactory* factory)
{
    m_gate = factory->createInPortGate(this, "gate");
    m_inports.append(m_gate);

    m_outPort = factory->createOutPortReplicable(this, "outPort");
    m_outports.append(m_outPort);

    m_attackDimmer = factory->createDimmer("Attack", ATTACK_MIN, ATTACK_MAX, ATTACK_DEFAULT, this);
    m_decayDimmer = factory->createDimmer("Decay", DECAY_MIN, DECAY_MAX, DECAY_DEFAULT, this);
    m_sustainDimmer = factory->createDimmer("Sustain", SUSTAIN_MIN, SUSTAIN_MAX, SUSTAIN_DEFAULT, this);
    m_releaseDimmer = factory->createDimmer("Release", RELEASE_MIN, RELEASE_MAX, RELEASE_DEFAULT, this);

}

void ADSR::ownProcess()
{
    qreal attackInSample = m_attackDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    qreal decayInSample = m_decayDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    qreal sustainInSample = m_sustainDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    qreal releaseInSample = m_releaseDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;



    if (0) {

        if (m_timeLine == 0) {
            // Begin of a ADSR cycle
            for (int i = 0;i < m_outPort->buffer()->length(); i++) {
                if (0) {

                }
            }

        } else {
            int i = 0;
            // A new gate signal end current running ADSR cycle
        }
    } else {
        int i = 0;
        // we continue the current running ADSR
    }













}
