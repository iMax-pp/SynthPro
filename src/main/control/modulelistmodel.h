#ifndef MODULELISTMODEL_H
#define MODULELISTMODEL_H

#include "factory/qtfactory.h"
#include <QAbstractListModel>
#include <QStringList>

/**
 * This class holds three lists for the different Module:
 *    -# Their names;
 *    -# Their pixmaps;
 *    -# Their ModuleType.
 *
 * It is intended to be used in the Docks on the presentation to display the Module.
 */
class ModuleListModel : public QAbstractListModel {
public:
    explicit ModuleListModel(QObject* parent = 0);

    /// Overrides QAbstractListModel::rowCount.
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    /// Overrides QAbstractListModel::flags.
    Qt::ItemFlags flags(const QModelIndex&) const;

    /// Overrides QAbstractListModel::data.
    QVariant data(const QModelIndex&, int = Qt::DisplayRole)const;

    /// Overrides QAbstractListModel::mimeData.
    QMimeData* mimeData(const QModelIndexList&) const;

    /// Overrides QAbstractListModel::mimeTypes.
    QStringList mimeTypes() const;

    /// Add a Module to the lists, by its name and ModuleType.
    void addModule(const QString& moduleName, const QtFactory::ModuleType);

private:
    QList<QString> m_moduleNames;
    QList<QPixmap> m_modulePixmaps;
    QList<QtFactory::ModuleType> m_moduleTypes;
};

#endif // MODULELISTMODEL_H
