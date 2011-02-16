#include "testwavlooper.h"

#include "abstraction/component/outport.h"
#include "abstraction/module/wavlooper.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QtTest/QTest>

void TestWavLooper::testWavLooper()
{
    QString inputFileName = ":src/resources/wav/testWavLooper.wav";

    SimpleFactory factory;
    WavLooper* wl = factory.createWavLooper(0);
    bool result = wl->newFile(inputFileName);

    if (result) {
        wl->process();

        qreal* data = wl->outports().at(0)->buffer()->data();
        int size = wl->outports().at(0)->buffer()->length();

        // Get the first data. They should be != 0 and different one from each other.
        qreal nb1 = data[0];
        qreal nb2 = data[1];
        result = (((nb1 != 0) && (nb2 != 0)) && (nb1 != nb2));

        // Check that each data read is nb1, and the one following is nb2.
        if (result) {
            int i = 0;
            while (result && (i < size)) {
                result = ((data[i] = nb1) && (data[i + 1] = nb2));
                i += 2;
            }
        }
    }

    QVERIFY(result);
}
