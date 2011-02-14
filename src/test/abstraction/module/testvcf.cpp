#include "testvcf.h"

#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/filter/filterincrement.h"
#include "abstraction/module/speaker.h"
#include "abstraction/module/vcf.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

#include <QDebug>

void TestVCF::testVCF()
{
    SimpleFactory factory;

    SynthPro* synthPro = factory.createSynthPro();

    // VCO
    VCO* vco = factory.createVCO(synthPro);
    vco->setShape("Empty");

    // VCF
    VCF* vcf = factory.createVCF(synthPro);
    vcf->setFilter("Increment");

    vco->outports().first()->connect(vcf->inports().first());

    vco->process();
    vcf->process();

    bool result = true;
    int i = 0;
    int size = vcf->outports().at(0)->buffer()->length();
    qreal* data = vcf->outports().at(0)->buffer()->data();
    while (result && (i < size)) {
        result = (data[i] == FilterIncrement::INCREMENT_VALUE);
        i++;
    }

    QVERIFY(result);

    delete synthPro;
}
