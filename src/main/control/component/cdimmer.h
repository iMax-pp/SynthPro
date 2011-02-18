#ifndef CDIMMER_H
#define CDIMMER_H

#include "abstraction/component/dimmer.h"
#include "presentation/component/pdimmer.h"
#include <QPointer>

typedef QString (*Format)(qreal);

class CDimmer : public Dimmer {
    Q_OBJECT

public:
    CDimmer(qreal min, qreal max, qreal defaultValue, qreal discretization, QObject* parent = 0);
    virtual ~CDimmer();

    inline PDimmer* presentation() const { return m_presentation; }
    void setPresentation(PDimmer*);

    /// Configure the formatting function used to display the value
    void setValueFormat(Format);

    /// Reimplements abstraction method to update the presentation
    void setValue(qreal);

    /// Synchronize the presentation’s value with the abstraction’s value, using the formatter
    void publishValue();

    /// Default formatting function
    static QString defaultFormat(qreal);
    static QString percentageFormat(qreal);
    static QString timeFormat(qreal);
    static QString gainFormat(qreal);

    /// Discretization factor
    static const qreal DISCR = 1000;

protected slots:
    /// Forward the value change event from the presentation to the abstraction (converting it into a qreal using the discretization factor)
    void valueChanged(int value);

private:
    QPointer<PDimmer> m_presentation;
    qreal m_discretization;
    Format m_valueFormat;
};

#endif // CDIMMER_H
