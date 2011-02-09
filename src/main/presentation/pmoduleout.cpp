#include "pmoduleout.h"

#include "control/cmoduleout.h"
#include "presentation/pport.h"
#include <QFont>

PModuleOut::PModuleOut(CModuleOut* control)
    : PModule(control)
{
}

void PModuleOut::initialize(PPort* pIn)
{
    setGeometry(0, 0, 100, 100);

    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("Out", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    pIn->setPos(-7, 45);
}
