#ifndef TILEPICKERLISTMODEL_H
#define TILEPICKERLISTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>

class TilePickerListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TilePickerItemRoles {
        NameRole = Qt::UserRole + 1
    };

    TilePickerListModel(QObject *parent = 0);

    /* For data handling */
    void addTileItem(const QString tileName);
    void clear();

    /* For QAbstrctListModel */
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<QString> m_tileItem;
};

#endif // TILEPICKERLISTMODEL_H
