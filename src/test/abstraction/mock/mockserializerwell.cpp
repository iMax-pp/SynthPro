#include "mockserializerwell.h"

#include "abstraction/buffer.h"
#include "factory/synthprofactory.h"

#include <QTextStream>

MockSerializerWell::MockSerializerWell(SynthPro* parent, QTextStream& output, SynthProFactory* factory)
    : Module(parent)
    , input(this, "input", factory)
    , m_output(output)
{
    m_inports.append(&input);
}

void MockSerializerWell::ownProcess()
{
    for (int i = 0 ; i < input.buffer()->length() ; i++) {
        m_output << input.buffer()->data()[i] << endl;
    }
}
