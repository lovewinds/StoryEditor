#include "view/ObjectTreeModel.h"
#include "view/ObjectTreeItem.h"

#include "view/CustomTreeData.h"

#include <QStringList>

ObjectTreeModel::ObjectTreeModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    m_roleNameMapping[TreeModelRoleName] = "name";

    QList<QVariant> rootData;
    rootData << "Name";
    rootItem = new ObjectTreeItem(rootData);

    /* Prepare data from text file */
    setupModelData(data.split(QString("\n")), rootItem);
}

ObjectTreeModel::~ObjectTreeModel()
{
    delete rootItem;
}

int ObjectTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        auto itm = static_cast<ObjectTreeItem*>(parent.internalPointer());
        return itm->columnCount();
    }

    return rootItem->columnCount();
}

QVariant ObjectTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != TreeModelRoleName)
        return QVariant();

    ObjectTreeItem *item = static_cast<ObjectTreeItem*>(index.internalPointer());

    return item->data(role - Qt::UserRole - 1);
}

Qt::ItemFlags ObjectTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant ObjectTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ObjectTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ObjectTreeItem*>(parent.internalPointer());

    ObjectTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ObjectTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ObjectTreeItem *childItem = static_cast<ObjectTreeItem*>(index.internalPointer());
    ObjectTreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ObjectTreeModel::rowCount(const QModelIndex &parent) const
{
    ObjectTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ObjectTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

QHash<int, QByteArray> ObjectTreeModel::roleNames() const
{
    return m_roleNameMapping;
}

QVariant ObjectTreeModel::newCustomTreeData(const QString &text, int position)
{
    CustomTreeData *t = new CustomTreeData(this);
    t->setText(text);
    t->setIndentation(position);
    QVariant v;
    v.setValue(t);
    return v;
}

void ObjectTreeModel::setupModelData(const QStringList &lines, ObjectTreeItem *parent)
{
    QList<ObjectTreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << newCustomTreeData(columnStrings[column], position);

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new ObjectTreeItem(columnData, parents.last()));
        }

        ++number;
    }
}
