#include "csampler.h"

CSampler::CSampler(SynthPro* parent)
    : Module(parent)
    , Sampler(parent)
    , CModule(parent)
{
}

void CSampler::initialize(SynthProFactory* factory)
{

}
