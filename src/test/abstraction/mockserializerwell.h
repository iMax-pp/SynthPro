#ifndef MOCKSERIALIZERWELL_H
#define MOCKSERIALIZERWELL_H

#include "abstraction/inport.h"
#include "abstraction/module.h"

class QTextStream;
class SynthProFactory;

/**
 * This class mocks a well module, which process operation serializes the content
 * of its input into a given QTextStream
 */
class MockSerializerWell : public Module {
    Q_OBJECT
public:
    MockSerializerWell(SynthPro*, QTextStream& output, SynthProFactory*);

    void ownProcess();

signals:

public slots:

public:
    InPort input;

private:
    QTextStream& m_output;
};

#endif // MOCKSERIALIZERWELL_H
