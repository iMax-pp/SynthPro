#ifndef CDIMMER_H
#define CDIMMER_H

#include "abstraction/component/dimmer.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pslider.h"

class CDimmer : public Dimmer {
    Q_OBJECT

public:
    CDimmer(qreal min, qreal max, qreal defaultValue, qreal discretization, QObject* parent = 0);

    PDimmer* presentation() const;
    void setPresentation(PDimmer*);

    /**
     * @param The value to convert.
     * @returns The "real life" value from the current value of the dimmer.
     */
    qreal realValue(qreal value) const;

    void updatePresentationValue(const QString&);

    /// Discretization factor
    static const qreal DISCR = 150;

public slots:
    void valueChanged(int value);

private:
    PDimmer* m_presentation;
    qreal m_discretization;
};

#endif // CDIMMER_H
