#include "poscilloscope.h"

#include "abstraction/buffer.h"
#include "control/coscilloscope.h"
#include "presentation/poscilloscopeview.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QGraphicsSimpleTextItem>

POscilloscope::POscilloscope(COscilloscope* control)
    : PModule(control)
{
}

void POscilloscope::initialize(PVirtualPort* input)
{
    TextWidget* title = new TextWidget("OSC", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    m_pOscilloscopeView = new POscilloscopeView(this);

    // Layout
    leftArea()->addAnchors(input, leftArea());
    bottomArea()->addAnchors(m_pOscilloscopeView, bottomArea());
    centerArea()->addAnchors(title, centerArea());
}

void POscilloscope::setVisualizedBuffer(Buffer* buffer)
{
    if (m_pOscilloscopeView) {
        m_pOscilloscopeView->setVisualizedBuffer(buffer);
    }
}

void POscilloscope::refreshOscilloscopeView()
{
    if  (m_pOscilloscopeView) {
        m_pOscilloscopeView->update(0, 0, m_pOscilloscopeView->WIDTH, m_pOscilloscopeView->HEIGHT);
    }
}
