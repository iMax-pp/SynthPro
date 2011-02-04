#ifndef MOCKINOUTMODULE_H
#define MOCKINOUTMODULE_H

#include "abstraction/mockmodule.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"

/**
 * Mock Module with an input port and an output port
 */
class MockInOutModule : public MockModule
{
public:
    MockInOutModule(const QString& msg, QTextStream& s, QObject* parent = 0);

    InPort input;
    OutPort output;
};

#endif // MOCKINOUTMODULE_H
