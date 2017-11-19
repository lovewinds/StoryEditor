#include "GridTileCanvasModel.h"

#include <QDebug>

/*****************************************************************************
 * GridTile
 *****************************************************************************/
GridTile::GridTile(int value) :
    m_value(value)
{
}

int GridTile::value() const
{
    return m_value;
}


/*****************************************************************************
 * GridTileCanvasModel
 *****************************************************************************/

GridTileCanvasModel::GridTileCanvasModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void GridTileCanvasModel::addTile(const GridTile& tile)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_tiles << tile;
    endInsertRows();
}


Qt::ItemFlags GridTileCanvasModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable;
}

int GridTileCanvasModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_tiles.count();
}

QVariant GridTileCanvasModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_tiles.count())
        return QVariant();

    const GridTile &tile = m_tiles[index.row()];
    if (role == ValueRole)
        return tile.value();

    return QVariant();
}

QHash<int, QByteArray> GridTileCanvasModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    return roles;
}
