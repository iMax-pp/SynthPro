#ifndef TESTWAVEGENERATOREMPTY_H
#define TESTWAVEGENERATOREMPTY_H

#include <QObject>

class TestWaveGeneratorEmpty : public QObject {
    Q_OBJECT

private slots:
    void testWaveGeneratorEmpty();

private:
    static const int BUFFER_LENGTH = 300;
};

#endif // TESTWAVEGENERATOREMPTY_H
