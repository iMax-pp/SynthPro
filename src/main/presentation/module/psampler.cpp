#include "psampler.h"

#include "control/module/csampler.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapbuttonwidget.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/textwidget.h"

#include <QFileDialog>
#include <QFont>
#include <QGraphicsAnchorLayout>

PSampler::PSampler(CSampler* control)
: PModule(control)
{
}

void PSampler::initialize(PVirtualPort* in, PVirtualPort* out, PVirtualPort* gate, PDimmer* bpm)
{
    TextWidget* title = new TextWidget(tr("Sampler"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    bpm->setSize(80, 80);

    m_record = new PixmapButtonWidget(":/src/resources/images/record-icon.png", this);
    connect(m_record, SIGNAL(clicked()), this, SLOT(recordClicked()));
    m_record->setActivated(true);

    m_stop = new PixmapButtonWidget(":/src/resources/images/stop-icon.png", this);
    connect(m_stop, SIGNAL(clicked()), this, SLOT(stopClicked()));
    m_stop->setActivated(false);

    m_play = new PixmapButtonWidget(":/src/resources/images/play-icon.png", this);
    connect(m_play, SIGNAL(clicked()), this, SLOT(playClicked()));
    m_play->setActivated(false);    

    // TODO Put a ProgressBar instead of a TextWidget.
    TextWidget* progressBar = new TextWidget("---------------", this);

    // Layout
    bottomArea()->addCornerAnchors(m_record, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(m_record, Qt::TopRightCorner, m_stop, Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(m_stop, Qt::TopRightCorner, m_play, Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(progressBar, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(progressBar, Qt::BottomRightCorner, gate, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(gate, Qt::BottomRightCorner, bpm, Qt::BottomLeftCorner);

    bottomArea()->addCornerAnchors(bpm, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(bpm, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);

    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    rightArea()->addAnchors(out, rightArea());
}

void PSampler::recordClicked()
{
    m_record->setActivated(false);
    m_stop->setActivated(true);
    m_play->setActivated(false);

    emit startRecordingClicked();
}

void PSampler::stopClicked()
{
    m_record->setActivated(false);
    m_stop->setActivated(false);
    m_play->setActivated(true);

    emit stopRecordingClicked();
}

void PSampler::playClicked()
{
    m_record->setActivated(false);
    m_stop->setActivated(true);
    m_play->setActivated(false);

    emit startPlayingClicked();
}
