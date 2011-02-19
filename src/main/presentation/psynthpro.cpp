#include "psynthpro.h"

#include "control/csynthpro.h"
#include "control/modulelistmodel.h"
#include "factory/qtfactory.h"
#include "presentation/widget/moduleview.h"

#include <QAction>
#include <QApplication>
#include <QDockWidget>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QListView>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

PSynthPro::PSynthPro(CSynthPro* control)
    : QMainWindow()
    , m_control(control)
{
    initUI();
    setMinimumSize(1024, 600);
}

void PSynthPro::setGraphicsScene(QGraphicsScene* scene)
{
    m_moduleView->setScene(scene);
}

CSynthPro* PSynthPro::control() const
{
    return m_control;
}

void PSynthPro::togglePlayPause()
{
    m_playPauseAct->toggle();
}

void PSynthPro::promptNew()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Are you <b>sure</b> you want to <b>erase</b> this magnificient work?"));
    msgBox.setInformativeText(tr("I mean, really, really ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if (msgBox.exec() == QMessageBox::Yes) {
        m_control->newScheme();
    }
}

void PSynthPro::promptSave()
{
    QString filename = QFileDialog::getSaveFileName(0, tr("Save File As"), "newScheme.synth",
                                                    tr("Synthetizer Scheme (*.synth)"));

    m_control->saveTo(filename);
}

void PSynthPro::about()
{
    QMessageBox::about(this, tr("About SynthPro"),
                       tr("<p>This <b>Wonderful Software</b> has been developped by "
                          "<b>The BackSynth Boys</b> featuring"
                          "<br/>- Cyrille Foliot"
                          "<br/>- Julien Névo"
                          "<br/>- Julien Richard-Foy"
                          "<br/>- Maxime Simon"
                          "<br/>from M2 Pro GL.</p>"
                         ));
}

void PSynthPro::initUI()
{
    // Create Menus & Main ToolBar.
    createStaticActions();
    createMenus();
    createMainToolBar();

    // Create Module Docks
    createDocks();
    createInputModuleList();
    createModuleList();
    createOutputModuleList();

    // Create QGraphicsView
    createGraphicsView();

    // Create Status Bar.
    statusBar()->showMessage(tr("Ready"));
}

void PSynthPro::createStaticActions()
{
    // Create "New" action.
    m_newAct = new QAction(QIcon(":/src/resources/images/new.png"), tr("&New"), this);
    m_newAct->setShortcuts(QKeySequence::New);
    m_newAct->setStatusTip(tr("Create a new file"));
    connect(m_newAct, SIGNAL(triggered()), this, SLOT(promptNew()));

    // Create "Save" action.
    m_saveAct = new QAction(QIcon(":/src/resources/images/save.png"), tr("&Save"), this);
    m_saveAct->setShortcuts(QKeySequence::Save);
    m_saveAct->setStatusTip(tr("Save the current scheme"));
    connect(m_saveAct, SIGNAL(triggered()), this, SLOT(promptSave()));

    // Create "Exit" action.
    m_exitAct = new QAction(QIcon(":/src/resources/images/exit.png"), tr("E&xit"), this);
    m_exitAct->setShortcut(tr("Ctrl+Q"));
    m_exitAct->setStatusTip(tr("Exit the application"));
    connect(m_exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Create "About" action.
    m_aboutAct = new QAction(tr("&About"), this);
    m_aboutAct->setStatusTip(tr("Show application's About box"));
    connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    // Create "About Qt" action.
    m_aboutQtAct = new QAction(tr("About &Qt"), this);
    m_aboutQtAct->setStatusTip(tr("Show Qt library's About box"));
    connect(m_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // Create "Play/Pause" action.
    m_playPauseAct = new QAction(QIcon(":src/resources/images/play.png"), tr("&Play/Pause"), this);
    m_playPauseAct->setCheckable(true);
    m_playPauseAct->setShortcut(tr("Ctrl+P"));
    m_playPauseAct->setStatusTip(tr("Play/Pause the application"));
    connect(m_playPauseAct, SIGNAL(triggered(bool)), m_control, SLOT(play(bool)));
}

void PSynthPro::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAct);
    m_fileMenu->addAction(m_saveAct);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_playPauseAct);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAct);

    menuBar()->addSeparator();

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutAct);
    m_helpMenu->addAction(m_aboutQtAct);
}

void PSynthPro::createMainToolBar()
{
    m_toolBar = addToolBar(tr("Main ToolBar"));
    m_toolBar->setFloatable(false);

    m_toolBar->addAction(m_newAct);
    m_toolBar->addAction(m_saveAct);
    m_toolBar->addAction(m_exitAct);

    m_toolBar->addSeparator();
    m_toolBar->addAction(m_playPauseAct);

    setUnifiedTitleAndToolBarOnMac(true);
}

void PSynthPro::createDocks()
{
    m_inModuleDock = new QDockWidget(tr("Input Modules"), this);
    m_inModuleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, m_inModuleDock);

    m_moduleDock = new QDockWidget(tr("Modules"), this);
    m_moduleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, m_moduleDock);

    m_outModuleDock = new QDockWidget(tr("Output Modules"), this);
    m_outModuleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, m_outModuleDock);
}

void PSynthPro::createGraphicsView()
{
    m_moduleView = new ModuleView(this, control());
    setCentralWidget(m_moduleView);
}

void PSynthPro::createModuleList()
{
    QListView* moduleList = new QListView;
    moduleList->setDragEnabled(true);
    moduleList->setDragDropMode(QListView::DragOnly);

    ModuleListModel* model = new ModuleListModel(this);
    model->addModule("VCF", QtFactory::VCFId);
    model->addModule("VCA", QtFactory::VCAId);
    model->addModule("ADSR", QtFactory::ADSRId);
    model->addModule("Delay", QtFactory::DelayId);
    model->addModule("Mixer", QtFactory::MixerId);
    model->addModule("Sampler", QtFactory::SamplerId);
    moduleList->setModel(model);

    m_moduleDock->setWidget(moduleList);
}

void PSynthPro::createInputModuleList()
{
    QListView* inModuleList = new QListView;
    inModuleList->setDragEnabled(true);
    inModuleList->setDragDropMode(QListView::DragOnly);

    ModuleListModel* model = new ModuleListModel(this);
    model->addModule("Keyboard", QtFactory::KeyboardId);
    model->addModule("VCO", QtFactory::VCOId);
    model->addModule("LFO", QtFactory::LFOId);
    model->addModule("WAV Looper", QtFactory::WavLooperId);
    inModuleList->setModel(model);

    m_inModuleDock->setWidget(inModuleList);
}

void PSynthPro::createOutputModuleList()
{
    QListView* outModuleList = new QListView;
    outModuleList->setDragEnabled(true);
    outModuleList->setDragDropMode(QListView::DragOnly);

    ModuleListModel* model = new ModuleListModel(this);
    model->addModule("Oscilloscope", QtFactory::OscilloscopeId);
    model->addModule("Audio Output", QtFactory::AudioOuputId);
    model->addModule("File Output", QtFactory::FileOutputId);
    outModuleList->setModel(model);

    m_outModuleDock->setWidget(outModuleList);
}
