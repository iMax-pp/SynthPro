#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "synthprofactory.h"

class QtFactory : public SynthProFactory
{
public:
    virtual SynthPro *createSynthPro();
};

#endif // QTFACTORY_H
