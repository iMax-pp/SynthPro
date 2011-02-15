#include "testsampler.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/vco.h"
#include "factory/simplefactory.h"

#include <QDebug>

void TestSampler::testSampler()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Sampler* sampler = factory.createSampler(synth);

    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connect(sampler->inports().first());

    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        vco->outports().first()->buffer()->data()[i] = 5;
    }

    sampler->process();

    qDebug() << "state " << sampler->state();


}
