#ifndef TESTVCA_H
#define TESTVCA_H

#include "abstraction/module/vca.h"

#include <QtTest/QTest>

class TestVCA : public QObject {
    Q_OBJECT

private slots:
    void testVCA();
};

#endif // TESTVCA_H
