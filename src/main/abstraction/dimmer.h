#ifndef DIMMER_H
#define DIMMER_H

#include <QObject>
/*
* A dimmer allow changing a float parameter of a module
*/
class Dimmer : public QObject {
    Q_OBJECT
public:
    Dimmer(float min, float max, float defaultValue, QObject *parent = 0);
    float value();
    void setValue(float);

private :
    float m_min;
    float m_max;
    float m_value;
};

#endif // DIMMER_H
