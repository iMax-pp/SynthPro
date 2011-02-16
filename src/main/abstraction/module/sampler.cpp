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

void Sampler::initialize(SynthProFactory * factory)
{
    m_inPort =  factory->createInPort(this, "in");
    m_inports.append(m_inPort);

    m_gate = factory->createInPortGate(this, "gate");
    m_inports.append(m_gate);

    m_outPort = factory->createOutPort(this, "out");
    m_outports.append(m_outPort);

    m_bpmDimmer = factory->createDialDimmer("bpm", MIN_BPM, MAX_BPM, DEFAULT_BPM, this);

    m_buffer = new Buffer(SAMPLER_MAX_DURATION*AudioDeviceProvider::OUTPUT_FREQUENCY);
    for (int i = 0 ; i < SAMPLER_MAX_DURATION*AudioDeviceProvider::OUTPUT_FREQUENCY ; i++) {
        m_buffer->data()[i] = 0;
    }
    m_record = factory->createPushButton("record", this);
    m_stop = factory->createPushButton("stop", this);
    m_play = factory->createPushButton("play", this);

    m_state = EMPTY;
}

void Sampler::ownProcess()
{
    int sampleMaxInByte = SAMPLER_MAX_DURATION*Buffer::DEFAULT_LENGTH;
 /*   for (int i = 0 ; i < 10 ; ++i){
        m_gate->buffer()->data()[i] = 0;
    }
    for (int i = 10 ; i < 100 ; ++i){
        m_gate->buffer()->data()[i] = 10;
    }
    for (int i = 100 ; i < 300 ; ++i){
        m_gate->buffer()->data()[i] = 0;
    }
    for (int i = 300 ; i < Buffer::DEFAULT_LENGTH ; ++i){
        m_gate->buffer()->data()[i] = 10;
    }
*/
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {

        if (m_gate->buffer()->data()[i] != 0) {
            m_gateState = true;
        } else {
            m_gateState = false;
        }
        bool gateUp = m_gateState && !m_oldGateState;
        //qDebug() <<  m_gate->buffer()->data()[i]  << state() << " " << gateUp << " " << m_gateState << " " << m_oldGateState;
        //if (i == 300) {qDebug() << "*********300*************";}


        if (m_state == RECORDING) {
            if (m_stop->pushed() || gateUp || m_bufferIndex == sampleMaxInByte) {
                m_state = WAITING;
                qDebug() << "stop record here ?" <<  m_bufferIndex <<" " << sampleMaxInByte;
            }  else if (m_bufferIndex < sampleMaxInByte){
                m_state = RECORDING;
            }
        }
        if (m_state == EMPTY) {
            if (m_record->pushed() || gateUp) {
                m_state = RECORDING;
                initializeBuffer();
            }
        }
        if (m_state == WAITING) {
            if (m_play->pushed() || gateUp) {
                qDebug() << "start playing ";
                // event gateUp has been used
                gateUp = !gateUp;
                m_state = PLAYING;
            }
            if (m_record->pushed()) {
                m_state = RECORDING;
                initializeBuffer();
            }
        }
        if (m_state == PLAYING) {
            if (m_stop->pushed() || gateUp) {
                m_state = WAITING;
            } else if (m_bufferIndex == m_sampleSize) {
                // if the buffer is entirely readed, restart the reading at begin of buffer
                m_bufferIndex = 0;
            }


        }

        switch (m_state) {
        case WAITING : break;
        case EMPTY : break;
        case PLAYING :
            m_outPort->buffer()->data()[i] = m_buffer->data()[m_bufferIndex * Buffer::DEFAULT_LENGTH + i];
            m_bufferIndex+=1;
            break;
        case RECORDING :
            m_buffer->data()[Buffer::DEFAULT_LENGTH*m_bufferIndex +i] = m_inPort->buffer()->data()[i];
            m_bufferIndex++;
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
    }
}
