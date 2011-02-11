#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "abstraction/component/selector.h"
#include "presentation/component/pselector.h"

class CSelector : public Selector {
public:
    CSelector(QList<int> choices, int defaultChoice, QObject* parent = 0);

    PSelector* presentation() const;
    void setPresentation(PSelector*);

private:
    PSelector* m_presentation;
};

#endif // CSELECTOR_H
