#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "abstraction/pushbutton.h"
#include "presentation/ppushbutton.h"

class CPushButton : public PushButton {
public:
    CPushButton(QObject* parent = 0);
    virtual ~CPushButton();

    PPushButton* presentation() const;
    void setPresentation(PPushButton*);

private:
    PPushButton* m_presentation;
};

#endif // CPUSHBUTTON_H
