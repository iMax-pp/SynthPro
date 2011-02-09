#include "pvcf.h"

#include "control/cvcf.h"
#include "pdimmer.h"
#include "pport.h"
#include "pselector.h"

#include <QFont>
#include <QGraphicsSimpleTextItem>

PVCF::PVCF(CVCF* control)
    : PModule(control)
{
}

void PVCF::initialize(PPort* in, PPort* cutOff, PPort* out, PSelector* selector, PDimmer* rDimmer, PDimmer* cutOffDimmer)
{
    // Resize PVCO to integrate the Components nicely.
    setGeometry(0, 0, 225, 175);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCF", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    in->setPos(-7, 70); // Yes, absolute positioning is bad.
    cutOff->setPos(110, 170);
    out->setPos(220, 70);

    rDimmer->setPos(10, 20);
    rDimmer->setMaximumSize(60, 60);

    cutOffDimmer->setPos(10, 95);
    cutOffDimmer->setMaximumSize(60, 60);

    selector->setPos(77, 0);
    selector->setMaximumSize(120, 175);
}
