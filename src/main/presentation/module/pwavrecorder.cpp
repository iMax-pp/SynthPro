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

    PixmapWidget* floppy = new PixmapWidget(":/src/resources/images/floppy-icon.png", false, this);
    connect(floppy, SIGNAL(clicked()), this, SLOT(floppyClicked()));

    m_stop = new PixmapWidget(":/src/resources/images/stop-icon.png", true, this);
    connect(m_stop, SIGNAL(clicked()), this, SLOT(stopClicked()));
    m_stop->setOpacity(0.5);

    m_record = new PixmapWidget(":/src/resources/images/record-icon.png", true, this);
    connect(m_record, SIGNAL(clicked()), this, SLOT(recordClicked()));
    m_record->setOpacity(0.5);

    m_close = new PixmapWidget(":/src/resources/images/close-icon.png", true, this);
    connect(m_close, SIGNAL(clicked()), this, SLOT(closeClicked()));
    m_close->setOpacity(0.5);

    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addCornerAnchors(m_record, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addAnchor(m_stop, Qt::AnchorLeft, m_record, Qt::AnchorRight);
    bottomArea()->addCornerAnchors(m_close, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);
    bottomArea()->addAnchor(m_record, Qt::AnchorBottom, floppy, Qt::AnchorTop);
    bottomArea()->addAnchor(m_stop, Qt::AnchorBottom, floppy, Qt::AnchorTop);
    bottomArea()->addAnchor(m_close, Qt::AnchorBottom, floppy, Qt::AnchorTop);
    bottomArea()->addCornerAnchors(floppy, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(floppy, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
}

QString PWavRecorder::askForFileName()
{
    QString fileName = QFileDialog::getSaveFileName(0, tr("Save File As"), "output.wav",
                                                    tr("Audio files (*.wav)"));

    if (!fileName.isNull()) {
        m_record->setOpacity(1);
        m_stop->setOpacity(0.5);
        m_close->setOpacity(1);
    }

    return fileName;
}

void PWavRecorder::floppyClicked()
{
    emit newFileClicked();
}

void PWavRecorder::recordClicked()
{
    m_record->setOpacity(0.5);
    m_stop->setOpacity(1);
    emit startRecordingClicked();
}

void PWavRecorder::stopClicked()
{
    m_record->setOpacity(1);
    m_stop->setOpacity(0.5);
    emit stopRecordingClicked();
}

void PWavRecorder::closeClicked()
{
    m_record->setOpacity(0.5);
    m_stop->setOpacity(0.5);
    m_close->setOpacity(0.5);
    emit closeFileClicked();
}
