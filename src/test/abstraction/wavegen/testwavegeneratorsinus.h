#ifndef TESTWAVEGENERATORSINUS_H
#define TESTWAVEGENERATORSINUS_H

#include <QObject>

/**
  * Test the generation of a Sinus wave. Requires linking a VCO with the
  * ModuleBufferRecorder. We don't test the signal coherence, this would be too
  * complicated. The output file has to be analysed with a sample editor, or
  * listened to by good ears.
  */
class TestWaveGeneratorSinus : public QObject {
    Q_OBJECT

private slots:
    void testWaveGeneratorSinus();

private:
    static const int NB_ITERATIONS = 200;
};

#endif // TESTWAVEGENERATORSINUS_H
