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
    // TODO move all that code below to the initialize method, using a PDimmer
    // and a PSelector (injected as parameters) instead of QDials.

    // Resize PVCO to integrate the Components nicely.
    setRect(0, 0, 225, 175);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCF", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));
}

void PVCF::initialize(PPort* in, PPort* cutOff, PPort* out, PSelector*, PDimmer*)
{
}
