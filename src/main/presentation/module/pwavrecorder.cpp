#include "pwavrecorder.h"

#include "control/module/cwavrecorder.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapbuttonwidget.h"
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
    connect(floppy, SIGNAL(clicked()), this, SLOT(floppyClicked()));

    m_stop = new PixmapButtonWidget(":/src/resources/images/stop-icon.png", this);
    connect(m_stop, SIGNAL(clicked()), this, SLOT(stopClicked()));
    m_stop->setActivated(false);

    m_record = new PixmapButtonWidget(":/src/resources/images/record-icon.png", this);
    connect(m_record, SIGNAL(clicked()), this, SLOT(recordClicked()));
    m_record->setActivated(false);

    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addCornerAnchors(m_record, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addAnchor(m_stop, Qt::AnchorLeft, m_record, Qt::AnchorRight);
    bottomArea()->addAnchor(m_record, Qt::AnchorBottom, floppy, Qt::AnchorTop);
    bottomArea()->addAnchor(m_stop, Qt::AnchorBottom, floppy, Qt::AnchorTop);
    bottomArea()->addCornerAnchors(floppy, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(floppy, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
}

QString PWavRecorder::askForFileName()
{
    QString fileName = QFileDialog::getSaveFileName(0, tr("Save File As"), "output.wav",
                                                    tr("Audio files (*.wav)"));

    if (!fileName.isNull()) {
        m_record->setActivated(true);
        m_stop->setActivated(false);
    }

    return fileName;
}

void PWavRecorder::floppyClicked()
{
    emit newFileClicked();
}

void PWavRecorder::recordClicked()
{
    m_record->setActivated(false);
    m_stop->setActivated(true);

    emit startRecordingClicked();
}

void PWavRecorder::stopClicked()
{
    m_record->setActivated(false);
    m_stop->setActivated(false);

    emit stopRecordingClicked();
}
