#include "testinport.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/port.h"
#include "factory/simplefactory.h"

void TestInPort::testOut()
{
    SimpleFactory factory;
    InPort* inPort = factory.createInPort(0, "in");

    QVERIFY(!inPort->out());

    delete inPort;
}

void TestInPort::testBuffer()
{
    SimpleFactory factory;
    InPort* in = factory.createInPort(0, "in");

    // By default an unconnected port has a buffer full of “0”
    for (int i = 0 ; i < in->buffer()->length() ; i++) {
        QCOMPARE(in->buffer()->data()[i], 0.0);
    }

    delete in;
}

void TestInPort::testConnectable()
{
    SimpleFactory factory;
    InPort* in = factory.createInPort(0, "in"); // Default input port, unreplicable, not a gate
    OutPort* out = factory.createOutPort(0, "in"); // Default output port, unreplicable, not a gate

    QVERIFY(in->connectable(out));
    QVERIFY(out->connectable(in));

    InPort* in2 = factory.createInPortReplicable(0, "in2"); // replicable input port
    OutPort* out2 = factory.createOutPortReplicable(0, "out2"); // replicable output port

    QVERIFY(in2->connectable(out2));
    QVERIFY(in2->connectable(out));
    QVERIFY(out2->connectable(in2));
    QVERIFY(out2->connectable(in));
    QVERIFY(in->connectable(out2));
    QVERIFY(!in->connectable(in2));
    QVERIFY(out->connectable(in2));
    QVERIFY(!out->connectable(out2));

    InPort* inGate = factory.createInPortGate(0, "in gate"); // unreplicable input gate
    OutPort* outGate = factory.createOutPortGate(0, "out gate"); // unreplicable output gate

    QVERIFY(inGate->connectable(outGate));
    QVERIFY(outGate->connectable(inGate));
    QVERIFY(!inGate->connectable(out));
    QVERIFY(!out->connectable(inGate));
    QVERIFY(!outGate->connectable(in));
    QVERIFY(!in->connectable(outGate));

    delete in;
    delete out;
    delete in2;
    delete out2;
    delete inGate;
    delete outGate;
}

void TestInPort::testConnectTo()
{
    SimpleFactory factory;
    InPort* in = factory.createInPort(0, "in");
    OutPort* out = factory.createOutPort(0, "out");
    m_count = 0;

    connect(in, SIGNAL(connectionsChanged()), SLOT(countVisit()));
    connect(out, SIGNAL(connectionsChanged()), SLOT(countVisit()));

    QVERIFY(in->connections().size() == 0);
    QVERIFY(out->connections().size() == 0);
    QCOMPARE(m_count, 0);

    Connection* c = in->connect(out);

    QVERIFY(in->connections().size() == 1);
    QVERIFY(out->connections().size() == 1);
    QVERIFY(in->connections().first() == c);
    QVERIFY(out->connections().first() == c);
    QCOMPARE(m_count, 1);

    delete in;
    delete out;
}

void TestInPort::testDisconnectFrom()
{
    SimpleFactory factory;
    InPort* in = factory.createInPort(0, "in");
    OutPort* out = factory.createOutPort(0, "out");
    m_count = 0;

    connect(in, SIGNAL(connectionsChanged()), SLOT(countVisit()));
    connect(out, SIGNAL(connectionsChanged()), SLOT(countVisit()));

    Connection* c = in->connect(out);
    out->disconnect(c);

    QVERIFY(in->connections().size() == 0);
    QVERIFY(out->connections().size() == 0);
    QCOMPARE(m_count, 2); // Two calls: one for the connection, one for the disconnection

    m_count = 0;
    out->connect(out); // Try to connect a port to itself
    in->connect(in);

    QVERIFY(!in->connections().size());
    QVERIFY(!out->connections().size());
    QCOMPARE(m_count, 0);

    in->disconnect(0); // Try to disconnect in from out though they were not connected

    QCOMPARE(m_count, 0);

    OutPort* outGate = factory.createOutPortGate(0, "out gate"); // Create a gate
    in->connect(outGate); // Try to connect to an incompatible port

    QCOMPARE(m_count, 0);

    delete in;
    delete out;
    delete outGate;
}

void TestInPort::testFetch()
{
    SimpleFactory factory;
    InPort* in = factory.createInPort(0, "in");
    OutPort* out = factory.createOutPort(0, "out");

    Buffer copyOfInitBuffer(*in->buffer());

    in->fetch();

    // Fetching when unconnected just clear the buffer
    QVERIFY(!memcmp(in->buffer()->data(), copyOfInitBuffer.data(), in->buffer()->length() * sizeof(*in->buffer()->data())));

    out->buffer()->data()[0] = 1;
    in->connect(out);

    // Out and in buffer are not identical
    QVERIFY(memcmp(out->buffer()->data(), in->buffer()->data(), in->buffer()->length() * sizeof(*in->buffer()->data())));

    in->fetch();

    // After fetching, in buffer is identical to out buffer
    QVERIFY(!memcmp(out->buffer()->data(), in->buffer()->data(), in->buffer()->length() * sizeof(*in->buffer()->data())));

    delete in;
    delete out;
}

void TestInPort::countVisit()
{
    m_count++;
}
