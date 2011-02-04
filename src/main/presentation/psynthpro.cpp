#include "psynthpro.h"

#include <QAction>
#include <QApplication>
#include <QDockWidget>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

PSynthPro::PSynthPro()
    : QMainWindow()
{
    initUI();
    setMinimumSize(640, 480);
}

void PSynthPro::promptNew()
{
    // FIXME Needs implementation.
    qDebug("[New Action] not implemented yet");
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

    // Create Module Dock
    createDocks();

    // Create QGraphicsView
    createGraphicsView();

    // Create Status Bar.
    statusBar()->showMessage(tr("Ready"));
}

void PSynthPro::createStaticActions()
{
    m_newAct = new QAction(QIcon(":/src/resources/images/new.png"), tr("&New"), this);
    m_newAct->setShortcuts(QKeySequence::New);
    m_newAct->setStatusTip(tr("Create a new file"));
    connect(m_newAct, SIGNAL(triggered()), this, SLOT(promptNew()));

    m_exitAct = new QAction(QIcon(":/src/resources/images/exit.png"), tr("E&xit"), this);
    m_exitAct->setShortcut(tr("Ctrl+Q"));
    m_exitAct->setStatusTip(tr("Exit the application"));
    connect(m_exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_aboutAct = new QAction(tr("&About"), this);
    m_aboutAct->setStatusTip(tr("Show application's About box"));
    connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    
    m_aboutQtAct = new QAction(tr("About &Qt"), this);
    m_aboutQtAct->setStatusTip(tr("Show Qt library's About box"));
    connect(m_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void PSynthPro::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAct);

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
    m_toolBar->addAction(m_newAct);
    m_toolBar->addAction(m_exitAct);
    m_toolBar->setFloatable(false);

    setUnifiedTitleAndToolBarOnMac(true);
}

void PSynthPro::createDocks()
{
    m_moduleDock = new QDockWidget(tr("Modules"), this);
    m_moduleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, m_moduleDock);    

    m_inModuleDock = new QDockWidget(tr("Input Modules"), this);
    m_inModuleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, m_inModuleDock);

    m_outModuleDock = new QDockWidget(tr("Output Modules"), this);
    m_outModuleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, m_outModuleDock);
}

void PSynthPro::createGraphicsView()
{
    m_graphicsView = new QGraphicsView(this);
    setCentralWidget(m_graphicsView);
}
