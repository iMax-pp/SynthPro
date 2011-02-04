#ifndef TESTSEQUENCER_H
#define TESTSEQUENCER_H

#include <QObject>

class TestSequencer : public QObject {
    Q_OBJECT

private slots:
    void testSortTwoModules();
    void testSortCyclingModules();
    void testSortTwoWells();
    void testSortNoWell();
};


#endif // TESTSEQUENCER_H
