#ifndef PSYNTHPRO_H
#define PSYNTHPRO_H

#include <QMainWindow>

class PSynthPro : public QMainWindow {
    Q_OBJECT

public:
    PSynthPro();

protected slots:
    void promptNew();

private:
    void initUI();
    void createStaticActions();

    QToolBar* m_toolBar;
    QDockWidget* m_moduleDock;

    QAction* m_newAct;
    QAction* m_exitAct;
};

#endif // PSYNTHPRO_H
