#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "abstraction/component/pushbutton.h"
#include "presentation/component/ppushbutton.h"

#include <QPointer>

/**
 * PushButton control class (PAC by inheritance).
 */
class CPushButton : public PushButton {
public:
    explicit CPushButton(QObject* parent = 0);
    virtual ~CPushButton();

    /// @returns the associated PPushButton presentation.
    inline PPushButton* presentation() const { return m_presentation; }

    /// @param presentation of type PPushButton to associate with this CPushButton.
    void setPresentation(PPushButton*);

private:
    QPointer<PPushButton> m_presentation;
};

#endif // CPUSHBUTTON_H
