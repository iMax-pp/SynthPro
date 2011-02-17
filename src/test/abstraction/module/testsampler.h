#ifndef TESTSAMPLER_H
#define TESTSAMPLER_H

#include "abstraction/module/sampler.h"

#include <QtTest/QTest>

class TestSampler : public QObject {
    Q_OBJECT

private slots:
    void testSampler();

private:
    void setValue(Buffer*, qreal);
};

#endif // TESTSAMPLER_H
