#include "csampler.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "presentation/module/psampler.h"

CSampler::CSampler(SynthPro* parent)
    : Module(parent)
    , Sampler(parent)
    , CModule(parent)
{
}

void CSampler::initialize(SynthProFactory* factory)
{
    Sampler::initialize(factory);

    CInPort* inPort = dynamic_cast<CInPort*>(m_inPort);
    COutPort* outPort = dynamic_cast<COutPort*>(m_outPort);
    CInPort* gate = dynamic_cast<CInPort*>(m_gate);
    CDimmer* bpmDimmer = dynamic_cast<CDimmer*>(m_bpmDimmer);

    PSampler* pre = dynamic_cast<PSampler*>(presentation());
    pre->initialize(inPort->presentation(), outPort->presentation(),
                    gate->presentation(), bpmDimmer->presentation());

    connect(pre, SIGNAL(startRecordingClicked()), this, SLOT(startRecording()));
    connect(pre, SIGNAL(stopRecordingClicked()), this, SLOT(stopRecording()));
    connect(pre, SIGNAL(startPlayingClicked()), this, SLOT(startPlaying()));
    connect(this, SIGNAL(valueChanged(int)), pre, SIGNAL(valueChanged(int)));
}

void CSampler::startRecording()
{
    Sampler::startRecording();
}

void CSampler::stopRecording()
{
    Sampler::stopRecording();
}

void CSampler::startPlaying()
{
    Sampler::startPlaying();
}
