#ifndef TESTINPORT_H
#define TESTINPORT_H

#include <QtTest/QTest>

class TestInPort : public QObject {
    Q_OBJECT

private slots:
    void testOut();
};

#endif // TESTINPORT_H
