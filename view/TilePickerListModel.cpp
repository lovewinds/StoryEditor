#include "view/TilePickerListModel.h"

TilePickerListModel::TilePickerListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void TilePickerListModel::addTileItem(const QString tileName)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_tileItem << tileName;
    endInsertRows();
}

void TilePickerListModel::clear()
{
    beginResetModel();
    m_tileItem.clear();
    endResetModel();
}

Qt::ItemFlags TilePickerListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable;
}

int TilePickerListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_tileItem.count();
}

QVariant TilePickerListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_tileItem.count())
        return QVariant();

    const QString &tileName = m_tileItem[index.row()];
    if (role == NameRole)
        return tileName;

    return QVariant();
}

QHash<int, QByteArray> TilePickerListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}
