#include "keyboard.h"

#include "abstraction/component/outport.h"
#include "factory/synthprofactory.h"

Keyboard::Keyboard(SynthPro* parent)
    : Module(parent)
    , m_keyPressedNumber(0)
    , m_pressed(false)
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::initialize(SynthProFactory* factory)
{
    if (factory) {
        // Creation of the frequency output.
        m_outPortFrequency = factory->createOutPortReplicable(this, tr("out"));
        m_outports.append(m_outPortFrequency);

        // Creation of the gate output.
        m_outPortGate = factory->createOutPortGate(this, tr("gate"));
        m_outports.append(m_outPortGate);
    }
}

void Keyboard::timerExpired()
{
}

void Keyboard::ownProcess()
{
    int valueGate;
    if (m_pressed) {
        valueGate = VALUE_GATE_ON;
    } else {
        valueGate = VALUE_GATE_OFF;
    }

    qreal* dataOutFrequency = m_outports.at(0)->buffer()->data();
    qreal* dataOutGate = m_outports.at(1)->buffer()->data();

    // Convert a key number into a tension.
    qreal valueFrequency = (qreal)m_keyPressedNumber / NUMBER_KEYS_IN_OCTAVE;

    for (int i = 0, size = m_outports.at(0)->buffer()->length(); i < size; i++) {
        // Fill the Gate out buffer. We consider the whole buffer has the same value.
        dataOutGate[i] = valueGate;
        // Fill the Frequency out buffer. Same remark as above.
        dataOutFrequency[i] = valueFrequency;
    }
}
