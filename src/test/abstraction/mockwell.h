#ifndef MOCKWELL_H
#define MOCKWELL_H

#include "abstraction/inport.h"
#include "abstraction/mockmodule.h"

/**
 * Mock Module with an input and no output (well)
 */
class MockWell : public MockModule {
public:
    MockWell(SynthPro*, const QString& msg, QTextStream&);

    InPort input;
};

#endif // MOCKWELL_H
