#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "abstraction/component/pushbutton.h"
#include "presentation/component/ppushbutton.h"
#include <QPointer>

class CPushButton : public PushButton {
public:
    CPushButton(QObject* parent = 0);
    virtual ~CPushButton();

    inline PPushButton* presentation() const { return m_presentation; }
    void setPresentation(PPushButton*);

private:
    QPointer<PPushButton> m_presentation;
};

#endif // CPUSHBUTTON_H
