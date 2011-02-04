#ifndef TESTSEQUENCER_H
#define TESTSEQUENCER_H

#include <QObject>

class TestSequencer : public QObject {
    Q_OBJECT

private slots:
    void testSortTwoModules();
};


#endif // TESTSEQUENCER_H
