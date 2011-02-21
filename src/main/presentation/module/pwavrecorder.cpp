#include "pwavrecorder.h"

#include "control/module/cwavrecorder.h"
#include "presentation/component/ppushbutton.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/textwidget.h"

#include <QFileDialog>
#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QIcon>

PWavRecorder::PWavRecorder(CWavRecorder* control)
    : PModule(control)
{
}

void PWavRecorder::initialize(PVirtualPort* in, PPushButton* record, PPushButton* stop)
{
    TextWidget* title = new TextWidget(tr("Rec"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    PixmapWidget* floppy = new PixmapWidget(":/src/resources/images/floppy.png", this);
    connect(floppy, SIGNAL(clicked()), this, SLOT(floppyClicked()));

    record->setIcon(QIcon(":/src/resources/images/record-icon.png"));
    stop->setIcon(QIcon(":/src/resources/images/stop-icon.png"));

    // Layout
    bottomArea()->addCornerAnchors(record, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(record, Qt::BottomRightCorner, stop, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(record, Qt::BottomLeftCorner, floppy, Qt::TopLeftCorner);

    bottomArea()->addCornerAnchors(floppy, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(floppy, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);

    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());

    bottomArea()->activate();
    layout()->activate();
}

QString PWavRecorder::askForFileName()
{
    return QFileDialog::getSaveFileName(0, tr("Save File As"), "output.wav",
                                        tr("Audio files (*.wav)"));
}

void PWavRecorder::floppyClicked()
{
    emit newFileClicked();
}
