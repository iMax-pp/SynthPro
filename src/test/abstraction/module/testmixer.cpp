#include "testmixer.h"

#include "abstraction/component/connection.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/vco.h"
#include "factory/simplefactory.h"

#include <QList>

void TestMixer::testMixer()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    VCO* vco  = factory.createVCO(synth);
    Mixer* mixer = factory.createMixer(synth);

    for (int i = 0 ; i < mixer->inports().size() ; i++) {
        vco->outports().first()->connect(mixer->inports().at(i));
    }
    mixer->ownProcess();


}
