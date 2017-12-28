#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QObject>
#include <QQuickItem>

#include "view/GridTilePickerImageProvider.h"
#include "view/GridTileCanvasImageProvider.h"
#include "view/GridTileCanvasModel.h"
#include "view/ObjectTreeModel.h"
#include "viewmodel/STViewModel.h"

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
    context->setContextProperty("viewModel", &myClass);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

#if 0
    /* Manual connect. It would be better on QML side */
    /* Signal connect, QML to C++ model */
    QObject *topLevel = engine.rootObjects().at(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    QObject *obj = window->children().at(3);

    QObject::connect(obj, SIGNAL(fileOpen(QString)),
                     &myClass, SLOT(onFileOpen(QString)));
    QObject::connect(obj, SIGNAL(qmlSignal(QString)),
                     &myClass, SLOT(cppSlot(QString)));
    QObject::connect(obj, SIGNAL(pickerSelected(QString)),
                     &myClass, SLOT(onPickerSelected(QString)));
#endif

    return app.exec();
}
