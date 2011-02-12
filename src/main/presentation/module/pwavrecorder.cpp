#include "pwavrecorder.h"

#include "control/module/cwavrecorder.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/textwidget.h"

#include <QFileDialog>
#include <QFont>
#include <QGraphicsAnchorLayout>

PWavRecorder::PWavRecorder(CWavRecorder* control)
    : PModule(control)
{
}

void PWavRecorder::initialize(PVirtualPort* in)
{
    TextWidget* title = new TextWidget(tr("Wav"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));
    
    PixmapWidget* floppy = new PixmapWidget(":/src/resources/images/floppy-icon.png", this);
    
    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(floppy, bottomArea());
}

QString PWavRecorder::askForFileName()
{
    return QFileDialog::getSaveFileName(0, tr("Save File As"), "output.wav", tr("Audio files (*.wav)"));
}
