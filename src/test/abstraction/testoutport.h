#ifndef TESTOUTPORT_H
#define TESTOUTPORT_H

#include <QtTest/QTest>

class TestOutPort : public QObject {
    Q_OBJECT

private slots:
    void testOut();
    void testSwapBuffers();
};

#endif // TESTOUTPORT_H
