#include "mockserializerwell.h"

#include "abstraction/buffer.h"

#include <QTextStream>

MockSerializerWell::MockSerializerWell(SynthPro* parent, QTextStream& output)
    : Module(parent)
    , input(this, "input")
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
