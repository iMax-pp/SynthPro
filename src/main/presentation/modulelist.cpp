#include "modulelist.h"

ModuleList::ModuleList(QWidget* parent)
    : QListWidget(parent)
{
    setSelectionMode(QListWidget::SingleSelection);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragOnly);
}
