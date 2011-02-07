#ifndef MODULELISTMODEL_H
#define MODULELISTMODEL_H

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

    void addModule(const QString& moduleName);

private:
    QList<QString> m_modules;
};

#endif // MODULELISTMODEL_H
