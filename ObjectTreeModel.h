#ifndef OBJECTTREEMODEL_H
#define OBJECTTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ObjectTreeItem;

class ObjectTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum TreeModelRoles
    {
        TreeModelRoleName = Qt::UserRole + 1
    };

    explicit ObjectTreeModel(const QString &data, QObject *parent = 0);
    ~ObjectTreeModel();

    /* QAbstractItemModel interface */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const override;

private:
    void setupModelData(const QStringList &lines, ObjectTreeItem *parent);
    QVariant newCustomTreeData(const QString &text, int position);

    ObjectTreeItem *rootItem;
    QHash<int, QByteArray> m_roleNameMapping;
};

#endif // OBJECTTREEMODEL_H
