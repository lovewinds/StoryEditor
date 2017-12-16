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
    Q_PROPERTY(int value READ value WRITE setValue)

public:
    enum GridTileRoles {
        ValueRole = Qt::UserRole + 1
    };

    GridTileCanvasModel(QObject *parent = 0);

    /* For data handling */
    void addTile();
    void clearTile();
    void removeTile();

    int value() const;
    void setValue(const int &value);

    /* For QAbstrctListModel */
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

signals:
    void tileCountChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<GridTile> m_tiles;
    int m_value;
};

#endif // GRIDTILECANVASMODEL_H
