#include "sampler.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/buffer.h"
#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/pushbutton.h"
#include "abstraction/synthpro.h"
#include "factory/synthprofactory.h"

#include <QDebug>

Sampler::Sampler(SynthPro* synth) 
    : Module(synth)
    , m_bufferIndex(0)
    , m_sampleSize(0)
    , m_gateState(false)
    , m_oldGateState(false)
{

}

Sampler::~Sampler()
{
    delete m_buffer;
}

void Sampler::initialize(SynthProFactory* factory)
{
    m_inPort = factory->createInPort(this, "in");
    m_inports.append(m_inPort);

    m_outPort = factory->createOutPort(this, "out");
    m_outports.append(m_outPort);

    m_gate = factory->createInPortGate(this, "gate");
    m_inports.append(m_gate);

    m_bpmDimmer = factory->createDialDimmer("bpm", MIN_BPM, MAX_BPM, DEFAULT_BPM, this);

    int length = SAMPLER_MAX_DURATION * AudioDeviceProvider::OUTPUT_FREQUENCY;

    m_buffer = new Buffer(length);
    for (int i = 0; i < length; i++) {
        m_buffer->data()[i] = 0;
    }

    m_state = EMPTY;
}

void Sampler::startRecording()
{
    m_state = RECORDING;
    initializeBuffer();
}

void Sampler::stopRecording()
{
    m_state = WAITING;
}

void Sampler::startPlaying()
{
    m_state = PLAYING;
}

void Sampler::ownProcess()
{
    int sampleMaxInByte = SAMPLER_MAX_DURATION * Buffer::DEFAULT_LENGTH;

    for (int i = 0; i < Buffer::DEFAULT_LENGTH; i++) {
        if (m_gate->buffer()->data()[i] != 0) {
            m_gateState = true;
        } else {
            m_gateState = false;
        }
        bool gateUp = m_gateState && !m_oldGateState;

        if (m_state == RECORDING && (gateUp || m_sampleSize == sampleMaxInByte)) {
            m_state = WAITING;
            qDebug() << "stop record here ?" <<  m_bufferIndex << " " << sampleMaxInByte;
        }

        if (m_state == EMPTY && gateUp) {
            startRecording();
        }

        if (m_state == WAITING && gateUp) {
            qDebug() << "start playing ";
            // event gateUp has been used
            gateUp = !gateUp;
            startPlaying();
        }

        if (m_state == PLAYING) {
            if (gateUp) {
                m_state = WAITING;
            }

            if (m_sampleSize == sampleMaxInByte) {
                // if the buffer is entirely readed, restart the reading at begin of buffer
                m_bufferIndex = 0;
            }
        }

        switch (m_state) {
        case WAITING : break;
        case EMPTY : break;
        case PLAYING :
            m_outPort->buffer()->data()[i] = m_buffer->data()[m_bufferIndex * Buffer::DEFAULT_LENGTH + i];
            break;
        case RECORDING :
            m_buffer->data()[Buffer::DEFAULT_LENGTH * m_bufferIndex + i] = m_inPort->buffer()->data()[i];
            emit valueChanged(m_sampleSize);
            // if we still record at the end of the buffer increment m_bufferIndex
            if (i == Buffer::DEFAULT_LENGTH - 1) {
                m_bufferIndex++;
            }

            m_sampleSize++;
            break;
        default : break;
        } // switch
        m_oldGateState = m_gateState;
    } // for

} // ownprocess()

void Sampler::initializeBuffer()
{
    m_bufferIndex = 0;
    m_sampleSize = 0;
}

QString Sampler::state()
{
    switch (m_state) {
    case WAITING : return "waiting";
    case PLAYING : return "playing";
    case RECORDING : return "recording";
    case EMPTY : return "empty";
    default: return "error";
    }
}
Buffer* Sampler::sampleBuffer()
{
    return m_buffer;
}
