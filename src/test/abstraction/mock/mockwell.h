#ifndef MOCKWELL_H
#define MOCKWELL_H

#include "abstraction/component/inport.h"
#include "abstraction/mock/mockmodule.h"
#include "factory/synthprofactory.h"

/**
 * Mock Module with an input and no output (well)
 */
class MockWell : public MockModule {
public:
    MockWell(SynthPro*, const QString& msg, QTextStream&, SynthProFactory*);

    InPort input;
};

#endif // MOCKWELL_H
