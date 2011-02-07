#ifndef TESTWAVEGENERATORTRIANGLE_H
#define TESTWAVEGENERATORTRIANGLE_H

#include <QObject>

/**
  * Test the generation of a Triangle wave. Requires linking a VCO with the
  * ModuleBufferRecorder. We don't test the signal coherence, this would be too
  * complicated. The output file has to be analysed with a sample editor, or
  * listened to by good ears.
  */
class TestWaveGeneratorTriangle : public QObject {
    Q_OBJECT

private slots:
    void testWaveGeneratorTriangle();

private:
    static const int NB_ITERATIONS = 200;
};

#endif // TESTWAVEGENERATORTRIANGLE_H
