#include "view/GridTilePickerModel.h"
#include <QDebug>

/*****************************************************************************
 * DotTile
 *****************************************************************************/
DotTile::DotTile(int value) :
    m_value(value)
{
}

int DotTile::value() const
{
    return m_value;
}

QString DotTile::name() const
{
    return m_name;
}

QColor DotTile::colorCode() const
{
    return m_color;
}

void DotTile::setValue(const int &value)
{
    m_value = value;
}

void DotTile::setName(const QString &name)
{
    m_name = name;
}

void DotTile::setColor(const QColor &color)
{
    m_color = color;
}

/*****************************************************************************
 * GridTilePickerModel
 *****************************************************************************/

GridTilePickerModel::GridTilePickerModel(QObject *parent)
    : QAbstractListModel(parent),
      m_tile_width(40), m_tile_height(40), m_value(0),
      m_horizontal_tile_count(0), m_vertical_tile_count(0)
{
}

unsigned int GridTilePickerModel::tileWidth() const
{
    return m_tile_width;
}

unsigned int GridTilePickerModel::tileHeight() const
{
    return m_tile_height;
}

unsigned int GridTilePickerModel::verticalTileCount() const
{
    return m_vertical_tile_count;
}

unsigned int GridTilePickerModel::horizontalTileCount() const
{
    return m_horizontal_tile_count;
}

void GridTilePickerModel::setTileWidth(unsigned int width)
{
    m_tile_width = width;
}

void GridTilePickerModel::setTileHeight(unsigned int height)
{
    m_tile_height = height;
}

void GridTilePickerModel::setHorizontalTileCount(unsigned int count)
{
    m_horizontal_tile_count = count;
}

void GridTilePickerModel::setVerticalTileCount(unsigned int count)
{
    m_vertical_tile_count = count;
}

void GridTilePickerModel::addTile()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    insertRow(rowCount());
    endInsertRows();
}

void GridTilePickerModel::clearTile()
{
    beginResetModel();
    removeRows(0, rowCount());
    m_tiles.clear();
    endResetModel();
}

void GridTilePickerModel::removeTile()
{
    beginRemoveRows(QModelIndex(), rowCount() - 1, rowCount() - 1);
    removeRows(rowCount() - 1, 1);
    endRemoveRows();
}

int GridTilePickerModel::value() const
{
    return m_value;
}

void GridTilePickerModel::setValue(const int &value)
{
    m_value = value;

    clearTile();
    for (int i = 0; i < m_value; i++)
        addTile();

    tileCountChanged();
}

bool GridTilePickerModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(count);
    Q_UNUSED(parent);

    m_tiles.append(DotTile(1));
    return true;
}

bool GridTilePickerModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (rowCount() <= 0)
        return false;

    m_tiles.removeLast();
    QAbstractListModel::removeRows(row, count, parent);

    return true;
}

Qt::ItemFlags GridTilePickerModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable;
}

int GridTilePickerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_tiles.count();
}

QVariant GridTilePickerModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_tiles.count())
        return QVariant();

    const DotTile &tile = m_tiles[index.row()];
    switch(role) {
    case ValueRole:
        return tile.value();
    break;
    case ColorRole:
        return tile.colorCode();
    break;
    case NameRole:
        return tile.name();
    break;
    }

    return QVariant();
}

QHash<int, QByteArray> GridTilePickerModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    roles[NameRole] = "name";
    roles[ColorRole] = "colorCode";
    return roles;
}
