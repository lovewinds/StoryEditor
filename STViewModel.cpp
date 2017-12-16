#include "STViewModel.h"
#include "GridTilePickerImageProvider.h"
#include "GridTileCanvasImageProvider.h"

#include <QQmlContext>
#include <QDebug>

STViewModel::STViewModel(QQmlApplicationEngine& app_engine)
    : engine(app_engine), context(NULL)
{
    engine.rootContext()->setContextProperty("picker_model", &picker_model);
    engine.rootContext()->setContextProperty("gridTileCanvasModel", &canvas_model);
}

void STViewModel::setContext(QQmlContext *context)
{
    this->context = context;
    if (context)
        context->setContextProperty("tilePickerListModel", &picker_list_model);
}

void STViewModel::cppSlot(const QString &msg)
{
    qDebug() << "Called the C++ slot with message:" << msg;

    picker_model.clearTile();
}

void STViewModel::prepareCanvas(std::string _name)
{
    std::string _path;
    unsigned int width = 0;
    unsigned int height = 0;
    GridTileCanvasImageProvider *canvas_provider
            = (GridTileCanvasImageProvider*)engine.imageProvider(QString("canvas_tiles"));

    _path = resource_model.getTilePath(_name);

    resource_model.getTileSize(_name, width, height);
    canvas_provider->setTileSource(QString::fromStdString(_path), width, height);
    canvas_provider->setModel(&(resource_model.getMapModel()));

    /* TODO: Update tile numbers and data */
    canvas_model.clearTile();
    canvas_model.setValue(8);
    qDebug() << "Canvas updated !";
}

void STViewModel::prepareTilePicker(std::string _name)
{
    std::string _path;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int vc = 0;
    unsigned int hc = 0;
    unsigned int tiles = 40;

    if (context)
        context->setContextProperty("tilePickerListModel", &picker_list_model);

    resource_model.getTileSize(_name, width, height);

    /* Load a specific tileset */
    GridTilePickerImageProvider *picker_provider = (GridTilePickerImageProvider*)engine.imageProvider(QString("tiles"));
    _path = resource_model.getTilePath(_name);
    /* TODO: Use 1st tileset from resource */
    qDebug() << "  Tile path: " << _path.c_str();
    picker_provider->setTileSource(QString::fromStdString(_path), width, height);
    tiles = picker_provider->tileCount();
    vc = picker_provider->verticalTileCount();
    hc = picker_provider->horizontalTileCount();

    /* TODO: Set valid number of tilesets */
    picker_model.clearTile();
    picker_model.setTileWidth(width);
    picker_model.setTileHeight(height);
    picker_model.setVerticalTileCount(vc);
    picker_model.setHorizontalTileCount(hc);

    /* TODO: setValue should be called in final step as it makes signal.
     * Should be considered in a valid way */
    picker_model.setValue(tiles);
}

void STViewModel::onFileOpen(const QString &path)
{
    std::string _name;
    qDebug() << "File opened: " << path;

    resource_model.openResourceData("../Resources/sample_scene.xml");

    /* Set model for TilePickerList */
    picker_list_model.clear();
    std::list<std::string> ls = resource_model.getTileList();
    for (auto it = ls.begin(); it != ls.end(); ++it) {
        picker_list_model.addTileItem(QString::fromStdString(it->data()));
        if (_name.length() == 0)
            _name = it->data();
    }
    prepareTilePicker(_name);

    _name = resource_model.getMapModel().getMapLayerName();
    prepareCanvas(_name);

    /* Notify loading finished event */
    loadedEvent();
}

void STViewModel::onPickerSelected(const QString &name)
{
    std::string _name = name.toUtf8().constData();
    std::string _path = resource_model.getTilePath(_name);
    QString path = QString::fromStdString(_path);

    prepareTilePicker(_name);
}
