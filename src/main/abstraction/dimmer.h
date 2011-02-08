#ifndef DIMMER_H
#define DIMMER_H

#include <QObject>
/*
* A dimmer allow changing a float parameter of a module
*/
class Dimmer : public QObject {
public:
    Dimmer(qreal min, qreal max, qreal defaultValue, QObject* parent = 0);
    qreal value() const;
    void setValue(qreal);

    inline qreal min() const { return m_min; }
    inline qreal max() const { return m_max; }

private :
    qreal m_min;
    qreal m_max;
    qreal m_value;
};

#endif // DIMMER_H
