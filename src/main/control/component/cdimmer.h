#ifndef CDIMMER_H
#define CDIMMER_H

#include "abstraction/component/dimmer.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pslider.h"

typedef QString (*Format)(qreal);

class CDimmer : public Dimmer {
    Q_OBJECT

public:
    CDimmer(qreal min, qreal max, qreal defaultValue, qreal discretization, QObject* parent = 0);

    PDimmer* presentation() const;
    void setPresentation(PDimmer*);

    /// Configure the formatting function used to display the value
    void setValueFormat(Format);

    /// Reimplements abstraction method to update the presentation
    void setValue(qreal);

    /// Synchronize the presentation’s value with the abstraction’s value, using the formatter
    void publishValue();

    /**
     * @param The value to convert.
     * @returns The "real life" value from the current value of the dimmer.
     */
    qreal realValue(qreal value) const;

    /// Default formatting function
    static QString defaultFormat(qreal);
    static QString percentageFormat(qreal);
    static QString timeFormat(qreal);
    static QString gainFormat(qreal);

    /// Discretization factor
    static const qreal DISCR = 150;

protected slots:
    /// Forward the value change event from the presentation to the abstraction (converting it into a qreal using the discretization factor)
    void valueChanged(int value);

private:
    PDimmer* m_presentation;
    qreal m_discretization;
    Format m_valueFormat;
};

#endif // CDIMMER_H
