#include "mockserializerwell.h"

#include "abstraction/buffer.h"

#include <QTextStream>

MockSerializerWell::MockSerializerWell(QTextStream& output, QObject* parent)
    : Module(parent)
    , input(this)
    , m_output(output)
{
    m_inports.append(&input);
}

void MockSerializerWell::process()
{
    fetchInput();
    for (int i = 0 ; i < input.buffer()->length() ; i++) {
        m_output << input.buffer()->data()[i] << endl;
    }
}
