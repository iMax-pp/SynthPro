#ifndef CMODULE_H
#define CMODULE_H

#include "abstraction/module.h"
#include "presentation/pmodule.h"

class CModule : public virtual Module {
public:
    CModule(QObject* parent = 0);
    virtual ~CModule();

    void setPresentation(PModule*);
    PModule* presentation() const;

    void move();

private:
    PModule* m_presentation;
};

#endif // CMODULE_H
