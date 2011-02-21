#include "cspeaker.h"

#include "control/component/cinport.h"
#include "presentation/module/pspeaker.h"

CSpeaker::CSpeaker(SynthPro* parent, QIODevice* device, QAudioOutput* output)
    : Module(parent)
    , Speaker(parent, device, output)
    , CModule(parent)
{
}

void CSpeaker::initialize(SynthProFactory* factory)
{
    Speaker::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);

    dynamic_cast<PSpeaker*>(presentation())->initialize(in->presentation());
}

QString CSpeaker::settings() const
{
    // Default implementation returns an empty string.
    return "";
}

void CSpeaker::setUpSettings(const QString&)
{
    // Default implementation do nothing (no settings to set up).
}
