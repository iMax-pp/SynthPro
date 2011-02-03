#ifndef SYNTHPROFACTORY_H
#define SYNTHPROFACTORY_H

class SynthPro;

class SynthProFactory
{
public:
    virtual SynthPro* createSynthPro() = 0;
};

#endif // SYNTHPROFACTORY_H
