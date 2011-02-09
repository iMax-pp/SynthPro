#include "pvcf.h"

#include "control/cvcf.h"
#include "presentation/pdimmer.h"
#include "presentation/pport.h"
#include "presentation/pselector.h"

#include <QFont>
#include <QGraphicsSimpleTextItem>

PVCF::PVCF(CVCF* control)
    : PModule(control)
{
}

void PVCF::initialize(PPort* in, PPort* cutOff, PPort* out, PSelector* selector, PDimmer* rDimmer, PDimmer* cutOffDimmer)
{
    // Resize PVCO to integrate the Components nicely.
    setGeometry(0, 0, 240, 200);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCF", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    in->setPos(-7, 70);
    in->setZValue(1);
    cutOff->setPos(110, 200);
    cutOff->setZValue(1);
    out->setPos(235, 70);
    out->setZValue(1);

    rDimmer->setPos(10, 20);
    rDimmer->setMaximumSize(90, 90);

    cutOffDimmer->setPos(10, 110);
    cutOffDimmer->setMaximumSize(90, 90);

    selector->setPos(100, 20);
    selector->setMaximumSize(120, 175);
}
