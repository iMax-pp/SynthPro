#include "presentation/widget/moduleview.h"

#include "control/csynthpro.h"
#include "factory/qtfactory.h"
#include <QDropEvent>

ModuleView::ModuleView(QWidget* parent, CSynthPro* cSynthPro)
    : QGraphicsView(parent)
    , m_cSynthPro(cSynthPro)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setAcceptDrops(true);
}

void ModuleView::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-synthpro")) {
        event->accept();
    } else {
        event->ignore();
    }
}

void ModuleView::dropEvent(QDropEvent* event)
{
    if (m_cSynthPro && event->mimeData()->hasFormat("application/x-synthpro")) {
        QtFactory::ModuleType moduleType = static_cast<QtFactory::ModuleType>(event->mimeData()->data("application/x-synthpro").toInt());
        m_cSynthPro->addModule(moduleType, mapToScene(event->pos()));
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

void ModuleView::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        qreal f = event->delta() > 0 ? 1.15 : 0.85;
        scale(f, f);
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}
