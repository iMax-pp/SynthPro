#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "abstraction/component/selector.h"
#include "presentation/component/pselector.h"
#include <QPointer>

class CSelector : public Selector {
public:
    CSelector(QList<int> choices, int defaultChoice, QObject* parent = 0);
    virtual ~CSelector();

    inline PSelector* presentation() const { return m_presentation; }
    void setPresentation(PSelector*);

private:
    QPointer<PSelector> m_presentation;
};

#endif // CSELECTOR_H
