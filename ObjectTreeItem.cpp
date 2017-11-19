#include "ObjectTreeItem.h"

#include <QStringList>

ObjectTreeItem::ObjectTreeItem(const QList<QVariant> &data, ObjectTreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

ObjectTreeItem::~ObjectTreeItem()
{
    qDeleteAll(m_childItems);
}

void ObjectTreeItem::appendChild(ObjectTreeItem *item)
{
    m_childItems.append(item);
}

ObjectTreeItem *ObjectTreeItem::child(int row)
{
    return m_childItems.value(row);
}

int ObjectTreeItem::childCount() const
{
    return m_childItems.count();
}

int ObjectTreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant ObjectTreeItem::data(int column) const
{
    return m_itemData.value(column);
}

ObjectTreeItem *ObjectTreeItem::parentItem()
{
    return m_parentItem;
}

int ObjectTreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ObjectTreeItem*>(this));

    return 0;
}
