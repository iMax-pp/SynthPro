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
    pOut->setPos(220, 70);

    pK->setPos(7, 90);
    pK->setMaximumSize(60, 60);

    pSel->setPos(77, 0);
    pSel->setMaximumSize(120, 175);
}
