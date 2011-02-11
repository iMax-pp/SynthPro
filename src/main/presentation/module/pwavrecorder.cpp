#include "pwavrecorder.h"

#include "control/module/cwavrecorder.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PWavRecorder::PWavRecorder(CWavRecorder* control)
    : PModule(control)
{
}

void PWavRecorder::initialize(PVirtualPort* in)
{
    TextWidget* title = new TextWidget("Wav", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));
    
    PixmapWidget* floppy = new PixmapWidget(":/src/resources/images/floppy-icon.png", this);
    
    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(floppy, bottomArea());
}
