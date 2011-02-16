#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include "abstraction/component/pushbutton.h"
#include "presentation/component/ppushbutton.h"

class CPushButton : public PushButton {
public:
    CPushButton(QObject* parent = 0);

    PPushButton* presentation() const;
    void setPresentation(PPushButton*);

    void setEnabled(bool);

private:
    PPushButton* m_presentation;
};

#endif // CPUSHBUTTON_H
