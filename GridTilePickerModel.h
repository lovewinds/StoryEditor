#ifndef DOTTILEIMAGEMODEL_H
#define DOTTILEIMAGEMODEL_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QQuickItem>
#include <QQmlListProperty>
#include <QAbstractListModel>

class DotTile
{

//    Q_PROPERTY(int value READ value WRITE setValue)
//    Q_PROPERTY(QString name READ name WRITE setName)
//    Q_PROPERTY(QColor colorCode READ colorCode WRITE setColorCode)

public:
    DotTile(int value);

    int value() const;
    QString name() const;
    QColor colorCode() const;

    void setValue(const int &value);
    void setName(const QString &name);
    void setColor(const QColor &color);

private:
    int m_value;
    QString m_name;
    QColor m_color;
};

class GridTilePickerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(unsigned int tileWidth READ tileWidth WRITE setTileWidth NOTIFY tileSizeChanged)
    Q_PROPERTY(unsigned int tileHeight READ tileHeight WRITE setTileHeight NOTIFY tileSizeChanged)
    Q_PROPERTY(unsigned int horizontalTileCount READ horizontalTileCount WRITE setHorizontalTileCount NOTIFY tileSizeChanged)
    Q_PROPERTY(unsigned int verticalTileCount READ verticalTileCount WRITE setVerticalTileCount NOTIFY tileSizeChanged)

public:
    enum GridTileRoles {
        ValueRole = Qt::UserRole + 1,
        ColorRole = Qt::UserRole + 2,
        NameRole = Qt::UserRole + 3
    };

    GridTilePickerModel(QObject *parent = 0);

    /* For data handling */
    void addTile();
    void clearTile();
    void removeTile();
    unsigned int tileWidth() const;
    unsigned int tileHeight() const;
    unsigned int horizontalTileCount() const;
    unsigned int verticalTileCount() const;
    void setTileWidth(unsigned int width);
    void setTileHeight(unsigned int height);
    void setHorizontalTileCount(unsigned int count);
    void setVerticalTileCount(unsigned int count);

    int value() const;
    void setValue(const int &value);

    QQmlListProperty<DotTile> tiles();

    /* For QAbstrctListModel */
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

signals:
    void tileSizeChanged();
    void tileCountChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<DotTile> m_tiles;
    int m_value;

    unsigned int m_tile_width;
    unsigned int m_tile_height;
    unsigned int m_horizontal_tile_count;
    unsigned int m_vertical_tile_count;
};

#endif // DOTTILEIMAGEMODEL_H
