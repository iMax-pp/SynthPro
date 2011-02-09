#include "pvca.h"

#include "control/cvca.h"
#include "pdimmer.h"
#include "pport.h"

#include <QFont>
#include <QGraphicsSimpleTextItem>

PVCA::PVCA(CVCA* control)
    : PModule(control)
{
}

void PVCA::initialize(PPort* in, PPort* out, PDimmer* dimmer)
{
    // Resize PVCO to integrate the Components nicely.
    setGeometry(0, 0, 130, 100);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCA", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    in->setPos(-7, 50); // Yes, absolute positioning is bad.
    in->setZValue(1);
    out->setPos(125, 50);
    out->setZValue(1);

    dimmer->setPos(20, 10);
    dimmer->setMaximumSize(90, 90);
}
