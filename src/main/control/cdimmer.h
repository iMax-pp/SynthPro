#ifndef CDIMMER_H
#define CDIMMER_H

#include "abstraction/dimmer.h"
#include "presentation/pdimmer.h"

class CDimmer : public Dimmer {
    Q_OBJECT

public:
    CDimmer(qreal min, qreal max, qreal defaultValue, qreal discretization, QObject* parent = 0);

    PDimmer* presentation() const;
    void setPresentation(PDimmer*);

public slots:
    void valueChanged(int value);

private:
    PDimmer* m_presentation;
    qreal m_discretization;
};

#endif // CDIMMER_H
