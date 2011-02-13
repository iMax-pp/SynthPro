#ifndef TESTWAVEGENERATORSAW_H
#define TESTWAVEGENERATORSAW_H

#include <QObject>

/**
  * Test the generation of a Saw wave. Requires linking a VCO with the
  * ModuleBufferRecorder. We don't test the signal coherence, this would be too
  * complicated. The output file has to be analysed with a sample editor, or
  * listened to by good ears.
  */
class TestWaveGeneratorSaw : public QObject {
    Q_OBJECT

private slots:
    void testWaveGeneratorSaw();

private:
    static const int NB_ITERATIONS = 200;
};


#endif // TESTWAVEGENERATORSAW_H
