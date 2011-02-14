#include "pwavlooper.h"

#include "control/module/cwavlooper.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapbuttonwidget.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/textwidget.h"

#include <QFileDialog>
#include <QFont>
#include <QGraphicsAnchorLayout>

PWavLooper::PWavLooper(CWavLooper* control)
    : PModule(control)
{
}

void PWavLooper::initialize(PVirtualPort* out)
{
    TextWidget* title = new TextWidget(tr("Looper"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    PixmapWidget* floppy = new PixmapWidget(":/src/resources/images/floppy-icon.png", this);
    connect(floppy, SIGNAL(clicked()), this, SLOT(floppyClicked()));

    // Layout
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(floppy, bottomArea());
//    bottomArea()->addCornerAnchors(floppy, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
//    bottomArea()->addCornerAnchors(floppy, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
}

QString PWavLooper::askForFileName()
{
    QString fileName = QFileDialog::getOpenFileName(0, tr("Load File"), "input.wav",
                                                    tr("Audio files (*.wav)"));
    if (!fileName.isNull()) {
//        m_record->setActivated(true);
//        m_stop->setActivated(false);
//        m_close->setActivated(true);
    }

    return fileName;
}

void PWavLooper::floppyClicked()
{
    emit newFileClicked();
}
