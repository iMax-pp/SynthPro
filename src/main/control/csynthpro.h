#ifndef CSYNTHPRO_H
#define CSYNTHPRO_H

#include "abstraction/synthpro.h"
#include "presentation/psynthpro.h"

class CSynthPro : public SynthPro {
private:
    PSynthPro* m_presentation;

public:
    CSynthPro();
    virtual ~CSynthPro();

    void setPresentation(PSynthPro*);
    PSynthPro* getPresentation() const;
};

#endif // CSYNTHPRO_H
