#ifndef DIMMER_H
#define DIMMER_H

#include <QObject>

/**
 * A dimmer allows changing a float parameter of a module.
 */
class Dimmer : public QObject {
    Q_OBJECT

public:
    /// Constructs a Dimmer from a min, max and defaultValue.
    Dimmer(qreal min, qreal max, qreal defaultValue, QObject* parent = 0);

    /// @returns the current value.
    inline qreal value() const { return m_value; }
    /// @param value to set this Dimmer to.
    virtual void setValue(qreal);

    /// @returns the min value.
    inline qreal min() const { return m_min; }
    /// @returns the max value.
    inline qreal max() const { return m_max; }

private :
    qreal m_min;
    qreal m_max;
    qreal m_value;
};

#endif // DIMMER_H
