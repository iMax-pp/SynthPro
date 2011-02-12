#include "delay.h"


#include "abstraction/audiodeviceprovider.h"
#include "abstraction/buffer.h"
#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "factory/synthprofactory.h"

#include <QDebug>


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
    m_delaySizeMax = BUFFER_DURATION_MAX *  AudioDeviceProvider::OUTPUT_FREQUENCY;


    m_buffer = new Buffer(m_delaySizeMax);


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
    // qDebug() << "buffer "  << m_buffer->length();
    int delaySize = m_durationDimmer->value() * AudioDeviceProvider::OUTPUT_FREQUENCY / Buffer::DEFAULT_LENGTH;

    m_readIndex = (m_readIndex > delaySize) ? 0 : m_readIndex;
    if (m_writeIndex > delaySize) {
        m_writeIndex = 0;
    }

    // qDebug() << "index " << m_readIndex << " " << m_writeIndex;
    // qDebug() << "delaySize"  << delaySize;
    // qDebug() << m_writeIndex << " " << m_readIndex;


    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        m_buffer->data()[m_writeIndex*Buffer::DEFAULT_LENGTH + i] = (m_inPort->buffer()->data()[i])*m_decayDimmer->value();
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        m_outPort->buffer()->data()[i] = m_buffer->data()[m_readIndex*Buffer::DEFAULT_LENGTH + i];
    }
    m_writeIndex++;
    m_readIndex++;
}

Buffer* Delay::buffer()
{
    return m_buffer;
}

