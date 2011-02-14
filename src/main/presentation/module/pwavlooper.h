#ifndef PWAVLOOPER_H
#define PWAVLOOPER_H

#include "presentation/pmodule.h"

class CWavLooper;
class PDimmer;
class PVirtualPort;

class PWavLooper : public PModule {
    Q_OBJECT

public:
    explicit PWavLooper(CWavLooper*);

    void initialize(PVirtualPort* out, PDimmer* speedDimmer);
    QString askForFileName();

private slots:
    void floppyClicked();

signals:
    void newFileClicked();
};

#endif // PWAVLOOPER_H
