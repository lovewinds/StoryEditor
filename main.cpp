#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QObject>
#include <QQuickItem>

#include "GridTilePickerImageProvider.h"
#include "GridTileCanvasImageProvider.h"
#include "GridTileCanvasModel.h"
#include "ObjectTreeModel.h"
#include "STViewModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Q_INIT_RESOURCE(qml);

    QQmlApplicationEngine engine;
    STViewModel myClass(engine);

    /* Image provider should be set before loading */
    engine.addImageProvider(QString("tiles"), new GridTilePickerImageProvider);
    engine.addImageProvider(QString("canvas_tiles"), new GridTileCanvasImageProvider);

    /* Read data from file */
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    ObjectTreeModel model(file.readAll());
    file.close();

    QQuickView view(&engine, NULL);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *context = view.rootContext();
    myClass.setContext(context);
    context->setContextProperty("theModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    /* Connect */
    QObject *topLevel = engine.rootObjects().at(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    QObject *obj = window->children().at(3);
    QObject::connect(obj, SIGNAL(fileOpen(QString)),
                     &myClass, SLOT(onFileOpen(QString)));
    QObject::connect(obj, SIGNAL(qmlSignal(QString)),
                     &myClass, SLOT(cppSlot(QString)));
    QObject::connect(obj, SIGNAL(pickerSelected(QString)),
                     &myClass, SLOT(onPickerSelected(QString)));

    QObject::connect(&myClass, SIGNAL(loadedEvent()),
                     obj, SLOT(on_load_finished()));

    return app.exec();
}
