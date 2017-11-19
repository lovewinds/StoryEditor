#ifndef GRIDTILECANVASMODEL_H
#define GRIDTILECANVASMODEL_H

#include <QObject>
#include <QAbstractListModel>

class GridTile
{
public:
    GridTile(int value);

    int value() const;

private:
    int m_value;
};

class GridTileCanvasModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum GridTileRoles {
        ValueRole = Qt::UserRole + 1
    };

    GridTileCanvasModel(QObject *parent = 0);

    /* For data handling */
    void addTile(const GridTile& tile);

    /* For QAbstrctListModel */
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<GridTile> m_tiles;
};

#endif // GRIDTILECANVASMODEL_H
