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
    , m_readIndex2(1)
    , m_writeIndex2(0)
{
}

Delay::~Delay()
{
    delete m_buffer1;
    delete m_buffer2;
}

void Delay::initialize(SynthProFactory* factory)
{
    m_delaySizeMax = BUFFER_DURATION_MAX *  AudioDeviceProvider::OUTPUT_FREQUENCY;


    m_buffer1 = new Buffer(m_delaySizeMax);
    m_buffer2 = new Buffer(m_delaySizeMax);

//    for (int i = 0 ; i < BUFFER_DURATION_MAX ; i++) {
        for (int i = 0 ; i < m_delaySizeMax ; i++) {
        m_buffer1->data()[i] = 0;
        m_buffer2->data()[i] = 0;
        // m_buffer2->data()[i + m_delaySizeMax] = 0;
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
    int delaySize = m_durationDimmer->value() * (AudioDeviceProvider::OUTPUT_FREQUENCY / Buffer::DEFAULT_LENGTH-1);

    m_readIndex = (m_readIndex > delaySize) ? 0 : m_readIndex;
    m_readIndex2 = (m_readIndex2 > delaySize) ? 0 : m_readIndex2;
    m_writeIndex2 = (m_writeIndex2 > delaySize) ? 0 : m_writeIndex2;



    if (m_writeIndex > delaySize) {
        m_writeIndex = 0;
    }

    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        qreal outdata = 0;


        outdata += m_buffer1->data()[m_readIndex*Buffer::DEFAULT_LENGTH + i];
        // set the buffer1 data on the buffer2 after multiply by decay
        m_buffer2->data()[m_writeIndex2*Buffer::DEFAULT_LENGTH + i] = outdata*m_decayDimmer->value();

        // add the buffer2 data to the output
        outdata += m_buffer2->data()[m_readIndex2*Buffer::DEFAULT_LENGTH + i];

        outdata += m_inPort->buffer()->data()[i];
        // write the output data in out buffer
        m_outPort->buffer()->data()[i] = outdata;


        // write on buffer1 the inport data
        m_buffer1->data()[m_writeIndex*Buffer::DEFAULT_LENGTH + i] = (m_inPort->buffer()->data()[i])*m_decayDimmer->value();
    }

    m_writeIndex++;
    m_readIndex++;
    m_readIndex2++;
    m_writeIndex2++;
}

Buffer* Delay::buffer1()
{
    return m_buffer1;
}

