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

void PVCO::initialize(PPort* vfm, PPort* out, PDimmer* kDimmer)
{
    vfm->setPos(0, 70); // Yes, absolute positioning is bad.
    out->setPos(200, 70);

    kDimmer->setPos(10, 90);
    kDimmer->setMaximumSize(60, 60);
}
