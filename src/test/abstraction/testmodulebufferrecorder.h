#ifndef TESTMODULEBUFFERRECORDER_H
#define TESTMODULEBUFFERRECORDER_H

#include <QObject>

/**
  * The test consists in linking a VCO with an empty WaveGenerator,
  * to the ModuleBufferRecorder. We then reload the file, skip the header, and
  * make sure the whole file is empty.
  */
class TestModuleBufferRecorder : public QObject {
    Q_OBJECT

private slots:
    void testModuleBufferRecorder();

private:
    static const int NB_ITERATIONS = 50;
    static const int SKIP_HEADER_OFFSET = 64; // Not accurate, but no needs to be.
};

#endif // TESTMODULEBUFFERRECORDER_H
