#ifndef MOCKMODULE_H
#define MOCKMODULE_H

#include "abstraction/module.h"

#include <QString>
#include <QTextStream>

/**
 * Basic Mock Module writing a message in a stream in its process operation
 */
class MockModule : public Module {
    Q_OBJECT

public:
    MockModule(const QString& msg, QTextStream&, QObject* parent = 0);

    /// Write the message in the stream
    void process();

signals:

public slots:

private:
    QString m_msg;
    QTextStream& m_s;
};

#endif // MOCKMODULE_H
