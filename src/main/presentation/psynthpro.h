#ifndef PSYNTHPRO_H
#define PSYNTHPRO_H

#include <QMainWindow>

class PSynthPro : public QMainWindow {
    Q_OBJECT

public:
    PSynthPro();

protected slots:
    void promptNew();
    void about();

private:
    void initUI();
    void createStaticActions();
    void createMenus();
    void createMainToolBar();
    void createModulesDock();

    QAction* m_newAct;
    QAction* m_exitAct;
    QAction* m_aboutAct;
    QAction* m_aboutQtAct;
    
    QToolBar* m_toolBar;
    QMenu* m_fileMenu;
    QMenu* m_helpMenu;
    QDockWidget* m_moduleDock;
};

#endif // PSYNTHPRO_H
