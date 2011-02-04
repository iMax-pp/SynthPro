#ifndef VCO_H
#define VCO_H

#include "module.h"

class WaveGenerator;

class VCO : public Module {
    Q_OBJECT
public:
    VCO(QObject* parent = 0);
    virtual void process();
    virtual QList<Module*>::const_iterator getReguirements() const;
    virtual void setWaveGenerator(WaveGenerator*);

protected:
    WaveGenerator* m_waveGenerator;
    InPort* m_defaultInPort;
    OutPort* m_defaultOutPort;
/*
* Initialization of the VCO
*/
    virtual void init();
};

#endif // VCO_H
