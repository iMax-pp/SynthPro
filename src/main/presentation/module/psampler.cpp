#include "psampler.h"

#include "control/module/csampler.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/ppushbutton.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/progressbarwidget.h"
#include "presentation/widget/textwidget.h"

#include <QFileDialog>
#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QIcon>

PSampler::PSampler(CSampler* control)
: PModule(control)
{
}

void PSampler::initialize(PVirtualPort* in, PVirtualPort* out, PVirtualPort* gate, PDimmer* bpm,
                          PPushButton* record, PPushButton* stop, PPushButton* play)
{
    TextWidget* title = new TextWidget(tr("Sampler"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    bpm->setSize(80, 80);

    record->setIcon(QIcon(":/src/resources/images/record-icon.png"));
    stop->setIcon(QIcon(":/src/resources/images/stop-icon.png"));
    play->setIcon(QIcon(":/src/resources/images/play-icon.png"));

    ProgressBarWidget* progressBar = new ProgressBarWidget(this);
    connect(this, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));
    connect(this, SIGNAL(lengthChanged(int)), progressBar, SLOT(setMaximum(int)));

    // Layout
    bottomArea()->addCornerAnchors(record, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(record, Qt::TopRightCorner, stop, Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(stop, Qt::TopRightCorner, play, Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(progressBar, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(progressBar, Qt::BottomRightCorner, gate, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(gate, Qt::BottomRightCorner, bpm, Qt::BottomLeftCorner);

    bottomArea()->addCornerAnchors(bpm, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(bpm, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);

    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    rightArea()->addAnchors(out, rightArea());

    bottomArea()->activate();
    layout()->activate();
}
