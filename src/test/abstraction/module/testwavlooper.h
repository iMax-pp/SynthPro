#ifndef TESTWAVLOOPER_H
#define TESTWAVLOOPER_H

#include <QObject>

/**
  * The test consists in loading a tiny Wav file consisted in 2 values
  * (high/low front) and checking if these 2 values cycle.
  */
class TestWavLooper : public QObject {
    Q_OBJECT

private slots:
    void testWavLooper();
};

#endif // TESTWAVLOOPER_H
