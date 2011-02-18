#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "abstraction/component/selector.h"
#include "presentation/component/pselector.h"

#include <QPointer>

/**
 * Selector control class (PAC by inheritance).
 */
class CSelector : public Selector {
public:
    CSelector(QList<int> choices, int defaultChoice, QObject* parent = 0);
    virtual ~CSelector();

    /// @returns the associated PSelector presentation.
    inline PSelector* presentation() const { return m_presentation; }

    /// @param presentation of type PSelector to associate with this CSelector.
    void setPresentation(PSelector*);

private:
    QPointer<PSelector> m_presentation;
};

#endif // CSELECTOR_H
