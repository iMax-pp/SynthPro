#ifndef TESTMODULEBUFFERRECORDER_H
#define TESTMODULEBUFFERRECORDER_H

#include <QObject>

class TestModuleBufferRecorder : public QObject {
    Q_OBJECT

private slots:
    void testModuleBufferRecorder();

private:
    static const int NB_ITERATIONS = 5;
};

#endif // TESTMODULEBUFFERRECORDER_H
