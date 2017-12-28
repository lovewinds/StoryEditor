#ifndef OBJECTTREEITEM_H
#define OBJECTTREEITEM_H

#include <QList>
#include <QVariant>

class ObjectTreeItem
{
public:
    explicit ObjectTreeItem(const QList<QVariant> &data, ObjectTreeItem *parentItem = 0);
    ~ObjectTreeItem();

    void appendChild(ObjectTreeItem *child);

    ObjectTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    ObjectTreeItem *parentItem();

private:
    QList<ObjectTreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    ObjectTreeItem *m_parentItem;
};

#endif // OBJECTTREEITEM_H
