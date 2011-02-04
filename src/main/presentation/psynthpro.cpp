#include "psynthpro.h"

#include <QAction>
#include <QToolBar>

PSynthPro::PSynthPro()
    : QMainWindow()
    , m_toolbar(0)
{
    initUI();
}

void PSynthPro::promptNew()
{
    qDebug("[New Action] not implemented yet");
}

void PSynthPro::initUI()
{
    // Create shiny toolbar.
    createStaticActions();

    m_toolbar = addToolBar(tr("MainToolBar"));
    m_toolbar->addAction(m_newAct);
    m_toolbar->addAction(m_exitAct);
    m_toolbar->setFloatable(false);

    setUnifiedTitleAndToolBarOnMac(true);
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
