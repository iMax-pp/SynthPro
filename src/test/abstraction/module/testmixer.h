#ifndef TESTMIXER_H
#define TESTMIXER_H

#include "abstraction/module/mixer.h"

#include <QtTest/QTest>

class TestMixer : public QObject {
    Q_OBJECT

private slots:
    void testMixer();
};

#endif // TESTMIXER_H
