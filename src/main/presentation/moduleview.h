#ifndef MODULEVIEW_H
#define MODULEVIEW_H

#include <QGraphicsView>

class CSynthPro;

class ModuleView : public QGraphicsView {
public:
    ModuleView(QWidget* parent = 0, CSynthPro* = 0);

protected:
    void dragEnterEvent(QDragEnterEvent*);
    void dragMoveEvent(QDragMoveEvent*);
    void dropEvent(QDropEvent*);

private:
    CSynthPro* m_cSynthPro;
};

#endif // MODULEVIEW_H
