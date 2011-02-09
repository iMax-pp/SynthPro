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
    setRect(0, 0, 225, 175);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCA", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    in->setPos(-7, 70); // Yes, absolute positioning is bad.
    out->setPos(220, 70);

    dimmer->setPos(65, 40);
    dimmer->setMaximumSize(90, 90);
}
