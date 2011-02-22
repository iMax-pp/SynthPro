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
    , m_inPort(0)
    , m_outPort(0)
    , m_buffer1(0)
    , m_buffer2(0)
    , m_buffer3(0)
    , m_durationDimmer(0)
    , m_decayDimmer(0)
    , m_delaySizeMax(BUFFER_DURATION_MAX * AudioDeviceProvider::OUTPUT_FREQUENCY)
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
    delete m_buffer3;
}

void Delay::initialize(SynthProFactory* factory)
{
    m_buffer1 = new Buffer(m_delaySizeMax);
    m_buffer2 = new Buffer(m_delaySizeMax);
    m_buffer3 = new Buffer(m_delaySizeMax);

    //    for (int i = 0 ; i < BUFFER_DURATION_MAX ; i++) {
    for (int i = 0 ; i < m_delaySizeMax ; i++) {
        m_buffer1->data()[i] = 0;
        m_buffer2->data()[i] = 0;
        m_buffer3->data()[i] = 0;
    }


    m_inPort = factory->createInPortReplicable(this, tr("in"));
    m_inports.append(m_inPort);

    m_outPort = factory->createOutPortReplicable(this, tr("out"));
    m_outports.append(m_outPort);

    m_decayDimmer = factory->createDialDimmer(tr("Decay"), DECAY_MIN, DECAY_MAX, DECAY_DEFAULT, this);
    m_durationDimmer = factory->createDialDimmer(tr("Duration"), DURATION_MIN, DURATION_MAX, DURATION_DEFAULT, this);

}

void Delay::ownProcess()
{
    int delaySize = m_durationDimmer->value() * (AudioDeviceProvider::OUTPUT_FREQUENCY / Buffer::DEFAULT_LENGTH-1);
    m_readIndex = m_readIndex % delaySize;
    m_writeIndex = m_writeIndex  % delaySize;

    int m_writeIndexMul = m_writeIndex*Buffer::DEFAULT_LENGTH;
    int m_readIndexMul = m_readIndex*Buffer::DEFAULT_LENGTH;
    qreal* ptBuffer1 = m_buffer1->data();
    qreal* ptBuffer2 = m_buffer2->data();
    qreal* ptBuffer3 = m_buffer3->data();

    qreal* ptOutBuffer = m_outPort->buffer()->data();
    qreal* ptInBuffer = m_inPort->buffer()->data();

    qreal decayDimmerValue = m_decayDimmer->value();

    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        qreal outdata = 0;

        outdata += ptBuffer1[m_readIndexMul + i];

        // set the buffer1 data on the buffer2 after multiply by decay
        ptBuffer2[m_writeIndexMul + i] = outdata * decayDimmerValue;
        ptBuffer3[m_writeIndexMul + i] = ptBuffer2[m_readIndexMul + i] * decayDimmerValue;

        // add the buffer2 data to the output
        outdata += ptBuffer2[m_readIndexMul + i];
        outdata += ptBuffer3[m_readIndexMul + i];

        outdata += ptInBuffer[i];

        // write the output data in out buffer
        ptOutBuffer[i] = outdata;

        // write on buffer1 the inport data
        ptBuffer1[m_writeIndexMul + i] = ptInBuffer[i] * decayDimmerValue;
    }

    m_writeIndex++;
    m_readIndex++;
}

Buffer* Delay::buffer1()
{
    return m_buffer1;
}

