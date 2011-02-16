#ifndef MODULELISTMODEL_H
#define MODULELISTMODEL_H

#include "factory/qtfactory.h"
#include <QAbstractListModel>
#include <QStringList>

class ModuleListModel : public QAbstractListModel {
public:
    ModuleListModel(QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex&) const;

    QVariant data(const QModelIndex&, int = Qt::DisplayRole)const;

    QMimeData* mimeData(const QModelIndexList&) const;
    QStringList mimeTypes() const;

    void addModule(const QString& moduleName, const QtFactory::ModuleType);

private:
    QList<QString> m_moduleNames;
    QList<QPixmap> m_modulePixmaps;
    QList<QtFactory::ModuleType> m_moduleTypes;
};

#endif // MODULELISTMODEL_H
