#include "pvco.h"

#include "control/cvco.h"
#include "pdimmer.h"
#include "pport.h"
#include "pselector.h"

#include <QFont>
#include <QGraphicsSimpleTextItem>

PVCO::PVCO(CVCO* control)
    : PModule(control)
{
}

void PVCO::initialize(PPort* pVfm, PPort* pOut, PSelector* pSel, PDimmer* pK)
{
    // Resize PVCO to integrate the Components nicely.
    setGeometry(0, 0, 225, 175);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCO", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    pVfm->setPos(-7, 70); // Yes, absolute positioning is bad.
    pVfm->setZValue(1);
    pOut->setPos(220, 70);
    pOut->setZValue(1);

    pK->setPos(0, 20);
    pK->setMaximumSize(90, 90);

    pSel->setPos(90, 20);
    pSel->setMaximumSize(120, 155);
}
