#include "moduleview.h"

#include "control/csynthpro.h"
#include <QDropEvent>

ModuleView::ModuleView(QWidget* parent, CSynthPro* cSynthPro)
    : QGraphicsView(parent)
    , m_cSynthPro(cSynthPro)
{
    setAcceptDrops(true);
}

void ModuleView::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void ModuleView::dropEvent(QDropEvent* event)
{
    if (m_cSynthPro && event->mimeData()->hasText()) {
        QString moduleType = event->mimeData()->text();
        m_cSynthPro->addModule(moduleType, event->pos());
        event->accept();
    } else {
        event->ignore();
    }
}

void ModuleView::dragMoveEvent(QDragMoveEvent* event)
{
    QGraphicsView::dragMoveEvent(event);
    event->accept();
}
