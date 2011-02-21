#ifndef PSYNTHPRO_H
#define PSYNTHPRO_H

#include <QMainWindow>

class CSynthPro;
class ModuleView;
class QGraphicsScene;

/**
 * Presentation of SynthPro.
 */
class PSynthPro : public QMainWindow {
    Q_OBJECT

public:
    explicit PSynthPro(CSynthPro*);

    /// Set the graphics scene for the module view.
    void setGraphicsScene(QGraphicsScene*);

    /// @returns the associated control.
    CSynthPro* control() const;

    /// Toggle Play/Pause button.
    void togglePlayPause();

    /// Display a given error when loading failed.
    void errorLoading(const QString& error);

protected slots:
    /// Ask if you <strong>REAAALLLYYY</strong> want to start a new project.
    void promptNew();
    /// Ask for a filename of scheme to open.
    void promptOpen();
    /// Ask for a filename to save the current scheme in.
    void promptSave();
    /// Display About Dialog.
    void about();

private:
    // UI Creation Methods.
    void initUI();
    void createStaticActions();
    void createMenus();
    void createMainToolBar();
    void createDocks();
    void createGraphicsView();

    void createModuleList();
    void createInputModuleList();
    void createOutputModuleList();

    CSynthPro* m_control;

    // UI Actions.
    QAction* m_newAct;
    QAction* m_openAct;
    QAction* m_saveAct;
    QAction* m_exitAct;
    QAction* m_aboutAct;
    QAction* m_aboutQtAct;
    QAction* m_playPauseAct;

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
