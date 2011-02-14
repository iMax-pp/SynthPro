#ifndef MIXER_H
#define MIXER_H

#include "abstraction/module.h"

class Dimmer;
class InPort;
class OutPort;
class SynthPro;
class SynthProFactory;

#include <QMap>

class Mixer : public virtual Module {
    Q_OBJECT
public:
    explicit Mixer(SynthPro*);
    virtual ~Mixer();
    virtual void initialize(SynthProFactory*);
    void ownProcess();
    static const int MIXER_SIZE = 4;

protected:
    QMap<InPort*, Dimmer*>* m_MixInPorts;
    OutPort* m_outPort;



};

#endif // MIXER_H
