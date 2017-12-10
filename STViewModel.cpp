#include "STViewModel.h"
#include "GridTilePickerImageProvider.h"

#include <QQmlContext>
#include <QDebug>

STViewModel::STViewModel(QQmlApplicationEngine& app_engine)
    : engine(app_engine), context(NULL)
{
    engine.rootContext()->setContextProperty("picker_model", &picker_model);
}

void STViewModel::setContext(QQmlContext *context)
{
    this->context = context;
}

void STViewModel::cppSlot(const QString &msg)
{
    qDebug() << "Called the C++ slot with message:" << msg;

    picker_model.clearTile();
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
    if (context)
        context->setContextProperty("tilePickerListModel", &picker_list_model);

    /* Load a specific tileset */
    GridTilePickerImageProvider *picker_provider = (GridTilePickerImageProvider*)engine.imageProvider(QString("tiles"));
    /* TODO: Use 1st tileset from resource */
    qDebug() << "  Tile path: " << resource_model.getTilePath(_name).c_str();
    picker_provider->setImageSource(QString::fromStdString(resource_model.getTilePath(_name)));

    /* TODO: Set valid number of tilesets */
    picker_model.clearTile();
    picker_model.setValue(40);

    /* Notify loading finished event */
    loadedEvent();
}

void STViewModel::onPickerSelected(const QString &name)
{
    static int val = 40;
    std::string path = name.toUtf8().constData();
    /* Load a specific tileset */
    GridTilePickerImageProvider *picker_provider = (GridTilePickerImageProvider*)engine.imageProvider(QString("tiles"));
    picker_provider->setImageSource(QString::fromStdString(resource_model.getTilePath(path)));

    /* Tile list need to be refreshed */
    /* TODO: Set valid number of tilesets */
    picker_model.clearTile();

    picker_model.setValue(val);
    val += 1;
}
