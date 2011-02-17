#include "sampler.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/buffer.h"
#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/pushbutton.h"
#include "abstraction/synthpro.h"
#include "control/component/cpushbutton.h"
#include "factory/synthprofactory.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>


Sampler::Sampler(SynthPro* synth) 
    : Module(synth)
    , m_bufferIndex(0)
    , m_sampleSize(0)
    , m_gateState(false)
    , m_oldGateState(false)
    , m_positionInBuffer(0)
{
}

Sampler::~Sampler()
{
    delete m_buffer;
}

void Sampler::initialize(SynthProFactory* factory)
{
    m_inPort = factory->createInPort(this, tr("in"));
    m_inports.append(m_inPort);

    m_outPort = factory->createOutPort(this, tr("out"));
    m_outports.append(m_outPort);

    m_gate = factory->createInPortGate(this, tr("gate"));
    m_inports.append(m_gate);

    m_bpmDimmer = factory->createDialDimmer(tr("Speed"), MIN_BPM, MAX_BPM, DEFAULT_BPM, this);

    m_recordButton = factory->createPushButton(tr("record"), this);
    m_stopButton = factory->createPushButton(tr("stop"), this);
    m_playButton = factory->createPushButton(tr("play"), this);

    dynamic_cast<CPushButton*>(m_recordButton)->setEnabled(true);
    dynamic_cast<CPushButton*>(m_stopButton)->setEnabled(false);
    dynamic_cast<CPushButton*>(m_playButton)->setEnabled(false);

    connect(m_recordButton, SIGNAL(buttonPushed()), this, SLOT(startRecording()));
    connect(m_stopButton, SIGNAL(buttonPushed()), this, SLOT(stopRecording()));
    connect(m_playButton, SIGNAL(buttonPushed()), this, SLOT(startPlaying()));

    int buffer_length = SAMPLER_MAX_DURATION * Buffer::DEFAULT_LENGTH;

    m_buffer = new Buffer(buffer_length);

    for (int i = 0; i < buffer_length; i++) {
        m_buffer->data()[i] = 0;
    }

    m_state = EMPTY;
}

void Sampler::startRecording()
{
    purgeBuffer(m_outPort->buffer());
    m_state = RECORDING;
    initializeBuffer();

    dynamic_cast<CPushButton*>(m_recordButton)->setEnabled(false);
    dynamic_cast<CPushButton*>(m_stopButton)->setEnabled(true);
    dynamic_cast<CPushButton*>(m_playButton)->setEnabled(false);
}

void Sampler::stopRecording()
{
    if (m_state == RECORDING) {
        // saveBuffer(m_buffer);
    }

    purgeBuffer(m_outPort->buffer());
    m_state = WAITING;

    dynamic_cast<CPushButton*>(m_recordButton)->setEnabled(true);
    dynamic_cast<CPushButton*>(m_stopButton)->setEnabled(false);
    dynamic_cast<CPushButton*>(m_playButton)->setEnabled(true);
}

void Sampler::startPlaying()
{
    m_state = PLAYING;
    m_bufferIndex = 0;

    dynamic_cast<CPushButton*>(m_recordButton)->setEnabled(false);
    dynamic_cast<CPushButton*>(m_stopButton)->setEnabled(true);
    dynamic_cast<CPushButton*>(m_playButton)->setEnabled(false);
}

void Sampler::ownProcess()
{
    qreal speed = m_bpmDimmer->value();
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
        }

        if (m_state == EMPTY && gateUp) {
            startRecording();
        }

        if (m_state == WAITING && gateUp) {
            // event gateUp has been used
            gateUp = !gateUp;
            startPlaying();
        }

        if (m_state == PLAYING) {
            if (gateUp) {
                m_state = WAITING;
            }

//            if (m_sampleSize == sampleMaxInByte) {
//                // if the buffer is entirely readed, restart the reading at begin of buffer
//                m_bufferIndex = 0;
//            }
        }

        switch (m_state) {
        case WAITING : break;

        case EMPTY : break;

        case PLAYING :
            m_positionInBuffer += speed;
            if (m_positionInBuffer >= m_sampleSize) {
                m_positionInBuffer = 0;
            }
         //   qDebug() << m_positionInBuffer << " " << m_bufferIndex << " " << m_sampleSize;
//            m_outPort->buffer()->data()[i] = m_buffer->data()[m_bufferIndex * Buffer::DEFAULT_LENGTH + i];
            m_outPort->buffer()->data()[i] = m_buffer->data()[/*m_bufferIndex * Buffer::DEFAULT_LENGTH +*/(int)m_positionInBuffer];
//            if (i == Buffer::DEFAULT_LENGTH - 1) {
//                m_bufferIndex++;
//        }
//            if (m_bufferIndex >= m_sampleSize / Buffer::DEFAULT_LENGTH) {
//                m_bufferIndex = 0;
//            }

            break;

        case RECORDING :
            m_buffer->data()[Buffer::DEFAULT_LENGTH * m_bufferIndex + i] = m_inPort->buffer()->data()[i];
          //  qDebug() << "buffer << " << m_inPort->buffer()->data()[i];
            emit valueChanged(m_sampleSize);

            // if we still record at the end of the buffer : increment m_bufferIndex
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

void Sampler::purgeBuffer(Buffer* buf)
{
    for (int i = 0; i < Buffer::DEFAULT_LENGTH; i++) {
        buf->data()[i] = 0;
    }
}
