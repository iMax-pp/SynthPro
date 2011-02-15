#include "testmixer.h"

#include "abstraction/component/connection.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/vco.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QList>

void TestMixer::testMixer()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    VCO* vco  = factory.createVCO(synth);
    Mixer* mixer = factory.createMixer(synth);

    // put 1 in the buffer
    for (int i = 0 ; i <  Buffer::DEFAULT_LENGTH ; i++) {
        vco->outports().first()->buffer()->data()[i] = 1;
    }
    vco->outports().first()->connect(mixer->inports().first());
    qDebug() << mixer->inports().at(0)->connections().size();

    mixer->process();
    bool res = true;
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        res &= mixer->outports().first()->buffer()->data()[i] == 2.5;
    }
    QVERIFY(res);

}
