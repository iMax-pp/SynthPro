#include "psynthpro.h"

#include <QAction>
#include <QDockWidget>
#include <QToolBar>

PSynthPro::PSynthPro()
    : QMainWindow()
    , m_toolBar(0)
    , m_moduleDock(0)
{
    initUI();
}

void PSynthPro::promptNew()
{
    qDebug("[New Action] not implemented yet");
}

void PSynthPro::initUI()
{
    // Create Main ToolBar.
    createStaticActions();

    m_toolBar = addToolBar(tr("Main ToolBar"));
    m_toolBar->addAction(m_newAct);
    m_toolBar->addAction(m_exitAct);
    m_toolBar->setFloatable(false);

    setUnifiedTitleAndToolBarOnMac(true);

    // Create Module Dock
    m_moduleDock = new QDockWidget(tr("Module Dock"), this);
    m_moduleDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, m_moduleDock);
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
    connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));
}
