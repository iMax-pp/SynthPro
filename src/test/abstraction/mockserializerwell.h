#ifndef MOCKSERIALIZERWELL_H
#define MOCKSERIALIZERWELL_H

#include "abstraction/inport.h"
#include "abstraction/module.h"

class QTextStream;

/**
 * This class mocks a well module, which process operation serializes the content
 * of its input into a given QTextStream
 */
class MockSerializerWell : public Module {
    Q_OBJECT
public:
    explicit MockSerializerWell(QTextStream& output, QObject* parent = 0);

    void process();

signals:

public slots:

public:
    InPort input;

private:
    QTextStream& m_output;
};

#endif // MOCKSERIALIZERWELL_H
