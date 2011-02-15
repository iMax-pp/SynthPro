#include "clfo.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cselector.h"
#include "presentation/module/plfo.h"
#include <qmath.h>

CLFO::CLFO(SynthPro* parent)
    : Module(parent)
    , LFO(parent)
    , CModule(parent)
{
}

void CLFO::initialize(SynthProFactory* factory)
{
    LFO::initialize(factory);

    COutPort* out = dynamic_cast<COutPort*>(m_out);
    CSelector* selector = dynamic_cast<CSelector*>(m_shapeSelector);
    CDimmer* k = dynamic_cast<CDimmer*>(m_kDimmer);
    CDimmer* range = dynamic_cast<CDimmer*>(m_rangeDimmer);
    CDimmer* offset= dynamic_cast<CDimmer*>(m_offsetDimmer);

    k->setValueFormat(formatK);
    range->setValueFormat(formatRange);
    offset->setValueFormat(formatOffset);

    dynamic_cast<PLFO*>(presentation())->initialize(out->presentation(), k->presentation(),
                                                    range->presentation(), offset->presentation(),
                                                    selector->presentation());
}

QString CLFO::formatK(qreal k)
{
    return QString::number(LFO::F0 * qPow(2, k)) + " Hz";
}

QString CLFO::formatRange(qreal range)
{
    return QString::number(range, 'g', 2); // FIXME Calculer en décibels ?
}

QString CLFO::formatOffset(qreal offset)
{
    return QString::number(offset, 'g', 2); // FIXME Quelle unité ? des millisecondes ?
}
