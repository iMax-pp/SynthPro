#ifndef PSYNTHPRO_H
#define PSYNTHPRO_H

#include <QMainWindow>

class CSynthPro;
class ModuleView;
class QGraphicsScene;

class PSynthPro : public QMainWindow {
    Q_OBJECT

public:
    PSynthPro(CSynthPro*);

    // Set the graphics scene for the module view.
    void setGraphicsScene(QGraphicsScene*);

    // Returns the associated control.
    CSynthPro* control() const;

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

    CSynthPro* m_control;

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
    ModuleView* m_moduleView;
};

#endif // PSYNTHPRO_H
