#include "sampler.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/buffer.h"
#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/pushbutton.h"
#include "abstraction/synthpro.h"
#include "factory/synthprofactory.h"

Sampler::Sampler(SynthPro* synth) 
    : Module(synth)
    , m_bufferIndex(0)
    , m_sampleSize(0)
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
    /*
    if (m_state == RECORDING) {
        if (m_stop->pushed()) {
            m_state = WAITING;
        }  else {
            m_state = RECORDING;
        }
    }
    if (m_state == EMPTY) {
        if (m_record->pushed()) {
            m_state = RECORDING;
            initializeBuffer();
        }
    }
    if (m_state == WAITING) {
        if (m_play->pushed()) {
            m_state = PLAYING;
        }
        if (m_record->pushed()) {
            m_state = RECORDING;
            initializeBuffer();
        }
    }
    if (m_state == PLAYING) {
        if (m_stop->pushed()) {
            m_state = WAITING;
        }
    }
    */
}

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
