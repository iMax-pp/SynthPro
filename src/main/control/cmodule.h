#ifndef CMODULE_H
#define CMODULE_H

#include "abstraction/module.h"
#include "presentation/pmodule.h"

#include <QObject>
#include <QPointer>

/**
 * Module control class (PAC by inheritance).
 */
class CModule : public virtual Module {
public:
    explicit CModule(SynthPro*);
    virtual ~CModule();

    /// @returns the associated PModule presentation.
    inline PModule* presentation() const { return m_presentation; }

    /// @param presentation of type PModule to associate with this CModule.
    void setPresentation(PModule*);

    /**
     * When moving the module around (event intercepted by PModule), this method
     * updates the position of the wire hooked to the ports.
     */
    void move();

private:
    QPointer<PModule> m_presentation;
};

#endif // CMODULE_H
