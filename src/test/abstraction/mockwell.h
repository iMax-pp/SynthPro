#ifndef MOCKWELL_H
#define MOCKWELL_H

#include "abstraction/mockmodule.h"
#include "abstraction/inport.h"

/**
 * Mock Module with an input and no output (well)
 */
class MockWell : public MockModule
{
public:
    MockWell(const QString& msg, QTextStream& s, QObject* parent = 0);

    InPort input;
};

#endif // MOCKWELL_H
