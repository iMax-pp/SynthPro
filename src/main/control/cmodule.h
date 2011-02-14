#ifndef CMODULE_H
#define CMODULE_H

#include "abstraction/module.h"
#include "presentation/pmodule.h"

class CModule : public virtual Module {
public:
    explicit CModule(SynthPro*);
    virtual ~CModule();

    void setPresentation(PModule*);
    PModule* presentation() const;

    /*
     * When moving the module around (event intercepted by PModule), this method
     * updates the position of the wire hooked to the ports.
     */
    void move();

private:
    PModule* m_presentation;
};

class Closer : public QObject {
    Q_OBJECT
public:
    Closer(CModule*);
protected slots:
    void onCloseClicked();
private:
    CModule* m_module;
};

#endif // CMODULE_H
