#ifndef PSYNTHPRO_H
#define PSYNTHPRO_H

#include <QMainWindow>

class QGraphicsView;

class PSynthPro : public QMainWindow {
    Q_OBJECT

public:
    PSynthPro();

protected slots:
    // Ask if you REAAALLLYYY want to start a new project.
    void promptNew();
    // Display About Dialog.
    void about();

private:
    // UI Creation Methods.
    void initUI();
    void createStaticActions();
    void createMenus();
    void createMainToolBar();
    void createDocks();
    void createGraphicsView();

    // UI Actions.
    QAction* m_newAct;
    QAction* m_exitAct;
    QAction* m_aboutAct;
    QAction* m_aboutQtAct;

    // UI Components.
    QToolBar* m_toolBar;
    QMenu* m_fileMenu;
    QMenu* m_helpMenu;
    QDockWidget* m_moduleDock;
    QDockWidget* m_inModuleDock;
    QDockWidget* m_outModuleDock;
    QGraphicsView* m_graphicsView;
};

#endif // PSYNTHPRO_H
