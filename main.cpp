#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "DotTileImageProvider.h"
#include "GridTileCanvasProvider.h"
#include "GridTileCanvasModel.h"
#include "ObjectTreeModel.h"
#include "model/SEMapModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Q_INIT_RESOURCE(qml);

    QQmlApplicationEngine engine;

    /* Image provider should be set before loading */
    engine.addImageProvider(QString("tiles"), new DotTileImageProvider);
    engine.addImageProvider(QString("canvas_tiles"), new GridTileCanvasProvider);

    /* Read data from file */
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    ObjectTreeModel model(file.readAll());
    file.close();

    GridTileCanvasModel gtc_model;
    for(int i = 0; i < 32; i++)
        gtc_model.addTile(GridTile(i+1));

    QQuickView view(&engine, NULL);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *context = view.rootContext();
    context->setContextProperty("gridTileCanvasModel", &gtc_model);
    context->setContextProperty("theModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    SEMapModel mapModel;
    mapModel.openMapData("../Resources/sample_scene.xml");

    return app.exec();
}
