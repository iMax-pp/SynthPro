#include "testvcf.h"

#include "abstraction/filterincrement.h"
#include "abstraction/inport.h"
#include "abstraction/moduleout.h"
#include "abstraction/outport.h"
#include "abstraction/synthpro.h"
#include "abstraction/vcf.h"
#include "abstraction/vco.h"
#include "factory/simplefactory.h"

#include <QDebug>

void TestVCF::testVCF()
{
    SynthPro synthPro(0);

    SimpleFactory factory;

    // VCO
    VCO* vco = factory.createVCO(&synthPro);
    vco->setShape("Empty");

    // VCF
    VCF* vcf = factory.createVCF(&synthPro);
    vcf->setFilter("Increment");

    vco->outports().at(0)->connectTo(vcf->inports().at(0));

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
}
