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

    // Layout
    leftArea()->addAnchors(in, leftArea());
    rightArea()->addAnchors(m_record, rightArea(), Qt::Horizontal);
    rightArea()->addAnchors(m_stop, rightArea(), Qt::Horizontal);
    rightArea()->addAnchor(m_record, Qt::AnchorTop, rightArea(), Qt::AnchorTop);
    rightArea()->addAnchor(m_record, Qt::AnchorBottom, m_stop, Qt::AnchorTop);
    rightArea()->addAnchor(m_stop, Qt::AnchorBottom, rightArea(), Qt::AnchorBottom);
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(floppy, bottomArea());
}

QString PWavRecorder::askForFileName()
{
    QString fileName = QFileDialog::getSaveFileName(0, tr("Save File As"), "output.wav", tr("Audio files (*.wav)"));

    if (!fileName.isNull()) {
        m_record->setOpacity(1);
        m_stop->setOpacity(0.5);
    }

    return fileName;
}

void PWavRecorder::floppyClicked()
{
    emit askNewFile();
}

void PWavRecorder::recordClicked()
{
    m_record->setOpacity(0.5);
    m_stop->setOpacity(1);
    emit startRecording();
}

void PWavRecorder::stopClicked()
{
    m_record->setOpacity(1);
    m_stop->setOpacity(0.5);
    emit stopRecording();
}
