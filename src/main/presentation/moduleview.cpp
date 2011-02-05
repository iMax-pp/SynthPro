#include "moduleview.h"

#include "control/csynthpro.h"
#include <QDragEnterEvent>

ModuleView::ModuleView(QWidget* parent, CSynthPro* cSynthPro)
    : QGraphicsView(parent)
    , m_cSynthPro(cSynthPro)
{
    setAcceptDrops(true);
}

void ModuleView::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        // TODO A feedback on drag enter in the graphics view?
        event->acceptProposedAction();
    }
}

void ModuleView::dropEvent(QDropEvent* event)
{
    if (m_cSynthPro) {
        QString moduleType = event->mimeData()->text();
        m_cSynthPro->addModule(moduleType, event->pos());
    }

    event->acceptProposedAction();
}
