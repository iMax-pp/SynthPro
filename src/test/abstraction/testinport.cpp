#include "testinport.h"

#include "abstraction/buffer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"

void TestInPort::testOut()
{
    InPort inPort(0);
    QVERIFY(!inPort.out());
}

void TestInPort::testBuffer()
{
    InPort in(0);

    // By default an unconnected port has a buffer full of “0”
    for (int i = 0 ; i < in.buffer()->length() ; i++) {
        QCOMPARE(in.buffer()->data()[i], 0.0);
    }
}

void TestInPort::testConnectable()
{
    InPort in(0); // Default input port, unreplicable, not a gate
    OutPort out(0); // Default output port, unreplicable, not a gate

    QVERIFY(in.connectable(&out));
    QVERIFY(out.connectable(&in));

    InPort in2(0, true); // replicable input port
    OutPort out2(0, true); // replicable output port

    QVERIFY(in2.connectable(&out2));
    QVERIFY(in2.connectable(&out));
    QVERIFY(out2.connectable(&in2));
    QVERIFY(out2.connectable(&in));
    QVERIFY(in.connectable(&out2));
    QVERIFY(!in.connectable(&in2));
    QVERIFY(out.connectable(&in2));
    QVERIFY(!out.connectable(&out2));

    InPort inGate(0, false, true); // unreplicable input gate
    OutPort outGate(0, false, true); // unreplicable output gate

    QVERIFY(inGate.connectable(&outGate));
    QVERIFY(outGate.connectable(&inGate));
    QVERIFY(!inGate.connectable(&out));
    QVERIFY(!out.connectable(&inGate));
    QVERIFY(!outGate.connectable(&in));
    QVERIFY(!in.connectable(&outGate));
}

void TestInPort::testConnectTo()
{
    InPort in(0);
    OutPort out(0);

    QVERIFY(!in.connections().contains(&out));
    QVERIFY(!out.connections().contains(&in));

    in.connectTo(&out);

    QVERIFY(in.connections().contains(&out));
    QVERIFY(out.connections().contains(&in));
}

void TestInPort::testFetch()
{
    InPort in(0);
    OutPort out(0);

    Buffer copyOfInitBuffer(*in.buffer());

    in.fetch();

    // Fetching when unconnected just clear the buffer
    QVERIFY(!memcmp(in.buffer()->data(), copyOfInitBuffer.data(), in.buffer()->length() * sizeof(*in.buffer()->data())));

    out.buffer()->data()[0] = 1;
    in.connectTo(&out);

    // Out and in buffer are not identical
    QVERIFY(memcmp(out.buffer()->data(), in.buffer()->data(), in.buffer()->length() * sizeof(*in.buffer()->data())));

    in.fetch();

    // After fetching, in buffer is identical to out buffer
    QVERIFY(!memcmp(out.buffer()->data(), in.buffer()->data(), in.buffer()->length() * sizeof(*in.buffer()->data())));
}
