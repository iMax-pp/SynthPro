#ifndef CMODULE_H
#define CMODULE_H

#include "abstraction/module.h"
#include "presentation/pmodule.h"

#include <QObject>

class CModule : public virtual Module {
public:
    explicit CModule(SynthPro*);
    virtual ~CModule();

    void setPresentation(PModule*);
    inline PModule* presentation() const { return m_presentation; }

    /*
     * When moving the module around (event intercepted by PModule), this method
     * updates the position of the wire hooked to the ports.
     */
    void move();

private:
    PModule* m_presentation;
};

#endif // CMODULE_H
