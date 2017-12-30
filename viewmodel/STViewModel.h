#ifndef ST_VIEW_MODEL_H
#define ST_VIEW_MODEL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QSize>

#include "model/SEResourceModel.h"
#include "view/GridTilePickerModel.h"
#include "view/GridTileCanvasModel.h"
#include "view/TilePickerListModel.h"

class STViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize mapSize READ mapSize WRITE setMapSize NOTIFY canvasResized)
    Q_PROPERTY(int pickTile READ pickTile WRITE setPickTile NOTIFY pickTileChanged)
    //Q_PROPERTY(QQmlListProperty<QString> tiles READ tiles)

public:
    STViewModel(QQmlApplicationEngine& app_engine);
    void setContext(QQmlContext *context);
    QSize mapSize() const;
    void setMapSize(const QSize size);
    int pickTile() const;
    void setPickTile(const int tile_idx);

signals:
    void loadedEvent();
    void canvasResized(int width, int height);
    void pickTileChanged(int index);

public slots:
    void onSave();
    void cppSlot(const QString &msg);
    void onFileOpen(const QString &path);
    void onPickerSelected(const QString &name);
    void onCanvasChanged(const int x, const int y, const int value);

protected:
    QQmlApplicationEngine& engine;
    QQmlContext *context;

    GridTilePickerModel picker_model;
    GridTileCanvasModel canvas_model;

    SEResourceModel resource_model;
    TilePickerListModel picker_list_model;

    void prepareCanvas(std::string name);
    void prepareTilePicker(std::string name);

    QSize m_mapSize;
    int m_pickTileIdx;
//    QList<QString> m_tiles;
};

#endif // ST_VIEW_MODEL_H
