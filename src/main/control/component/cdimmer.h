#ifndef CDIMMER_H
#define CDIMMER_H

#include "abstraction/component/dimmer.h"
#include "presentation/component/pdimmer.h"
#include <QPointer>

typedef QString (*Format)(qreal);

/**
 * Dimmer control class (PAC by inheritance).
 */
class CDimmer : public Dimmer {
    Q_OBJECT

public:
    CDimmer(qreal min, qreal max, qreal defaultValue, qreal discretization, QObject* parent = 0);
    virtual ~CDimmer();

    /// @returns The associated PDimmer presentation.
    inline PDimmer* presentation() const { return m_presentation; }

    /// @param presentation of type PDimmer to associate with this CDimmer.
    void setPresentation(PDimmer*);

    /// Configure the formatting function used to display the value.
    void setValueFormat(Format);

    /// Reimplements abstraction method to update the presentation.
    void setValue(qreal);

    /// Default formatting function.
    static QString defaultFormat(qreal);
    /// Percentage formatting function.
    static QString percentageFormat(qreal);
    /// Time formatting function.
    static QString timeFormat(qreal);
    /// Gain formatting function.
    static QString gainFormat(qreal);

    /// Discretization factor.
    static const qreal DISCR = 1000;

protected slots:
    /**
     * Forward the value change event from the presentation to the abstraction
     * (converting it into a qreal using the discretization factor).
     */
    void valueChanged(int value);

protected:
    /// Synchronize the presentation value with the abstraction value, using the formatter.
    void publishValue();


private:
    QPointer<PDimmer> m_presentation;
    qreal m_discretization;
    Format m_valueFormat;
};

#endif // CDIMMER_H
