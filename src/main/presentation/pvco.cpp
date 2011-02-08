#include "pvco.h"

#include "control/cvco.h"
#include "pdimmer.h"
#include <QDial>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>

PVCO::PVCO(CVCO* control)
    : PModule(control)
{
    // TODO move all that code below to the initialize method, using a PDimmer
    // and a PSelector (injected as parameters) instead of QDials.

    // Resize PVCO to integrate the Components nicely.
    setRect(0, 0, 200, 150);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCO", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));
}

void PVCO::initialize(PPort* pVfm, PPort* pOut, PDimmer* pK)
{
    /*pVfm->setParentItem(settings());
    pK->setParentItem(settings());
    pK->setMaximumSize(60, 60);

    pOut->setParentItem(out());

    doLayout();*/
    pVfm->setPos(0, 70); // Yes, absolute positioning is bad.
    pOut->setPos(200, 70);

    pK->setPos(10, 90);
    pK->setMaximumSize(60, 60);
}
