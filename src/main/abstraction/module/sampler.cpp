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

    m_bpmDimmer = factory->createDimmer("bpm", MIN_BPM, MAX_BPM, DEFAULT_BPM, this);

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
    if (m_state == RECORDING) {
        if (m_stop->pushed()) {
            m_state = WAITING;
        }  else {
            m_state = RECORDING;
        }
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {

    }


    // Ananlysis of gate
    int startIndex = -1;
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        if (m_gate->buffer()->data()[i] != 0) {
            startIndex = i;
        }
    }
}
