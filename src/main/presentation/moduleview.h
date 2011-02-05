#ifndef MODULEVIEW_H
#define MODULEVIEW_H

#include <QGraphicsView>

class CSynthPro;

class ModuleView : public QGraphicsView {
public:
    ModuleView(QWidget* parent = 0, CSynthPro* = 0);

protected:
    virtual void dragEnterEvent(QDragEnterEvent*);
    virtual void dropEvent(QDropEvent*);

private:
    CSynthPro* m_cSynthPro;
};

#endif // MODULEVIEW_H
