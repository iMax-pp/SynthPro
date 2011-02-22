#ifndef TESTINPORT_H
#define TESTINPORT_H

#include <QtTest/QTest>

class TestInPort : public QObject {
    Q_OBJECT

public:
    TestInPort() {}

public slots:
    void countVisit();

private slots:
    void testOut();
    void testBuffer();
    void testConnectable();
    void testConnectTo();
    void testDisconnectFrom();
    void testFetch();

private:
    int m_count;
};

#endif // TESTINPORT_H
