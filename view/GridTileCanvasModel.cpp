#include "view/GridTileCanvasModel.h"

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
    : QAbstractListModel(parent),
      m_value(0)
{
}

void GridTileCanvasModel::addTile()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    insertRow(rowCount());
    endInsertRows();
}

void GridTileCanvasModel::clearTile()
{
    beginResetModel();
    //removeRows(0, rowCount());
    m_tiles.clear();
    endResetModel();

    qDebug() << "Removed. Left: [" << m_tiles.count() << "]";
}

void GridTileCanvasModel::removeTile()
{
    beginRemoveRows(QModelIndex(), rowCount() - 1, rowCount() - 1);
    removeRows(rowCount() - 1, 1);
    endRemoveRows();
}

int GridTileCanvasModel::value() const
{
    return m_value;
}

void GridTileCanvasModel::setValue(const int &value)
{
    m_value = value;

    clearTile();
    for (int i = 0; i < m_value; i++)
        addTile();

    tileCountChanged();
}

bool GridTileCanvasModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(count);
    Q_UNUSED(parent);

    m_tiles.append(GridTile(1));
    return true;
}

bool GridTileCanvasModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (rowCount() <= 0)
        return false;

    m_tiles.removeLast();
    QAbstractListModel::removeRows(row, count, parent);
    return true;
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
