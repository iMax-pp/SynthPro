#include "delay.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/buffer.h"
#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "factory/synthprofactory.h"

Delay::Delay(SynthPro* parent)
    : Module(parent)
    , m_readIndex(1)
    , m_writeIndex(0)
{
}

Delay::~Delay()
{
    delete m_buffer;
}

void Delay::initialize(SynthProFactory* factory)
{
    m_delaySize_max = BUFFER_DURATION_MAX *  AudioDeviceProvider::OUTPUT_FREQUENCY  / Buffer::DEFAULT_LENGTH;

    m_buffer = new Buffer(BUFFER_DURATION_MAX);

    for (int i = 0 ; i < BUFFER_DURATION_MAX ; i++) {
        m_buffer->data()[i] = 0;
    }


    m_inPort = factory->createInPortReplicable(this, "inPort");
    m_inports.append(m_inPort);

    m_outPort = factory->createOutPortReplicable(this, "outPort");
    m_outports.append(m_outPort);

    m_decayDimmer = factory->createDimmer("Decay", DECAY_MIN, DECAY_MAX, DECAY_DEFAULT, this);
    m_durationDimmer = factory->createDimmer("Duration", DURATION_MIN, DURATION_MAX, DURATION_DEFAULT, this);


}

void Delay::ownProcess()
{
    int delaySize = m_durationDimmer->value();
    int decay = m_durationDimmer->value();

    m_readIndex = (m_readIndex == delaySize - 1) ? 0 : m_writeIndex + 1;

    if (m_writeIndex == delaySize) {
        m_readIndex = 0;
    }

    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        m_outPort->buffer()->data()[i] = m_buffer->data()[m_readIndex + i];
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        m_buffer->data()[m_writeIndex + i] = m_inPort->buffer()->data()[i];
    }

    m_writeIndex++;
}
