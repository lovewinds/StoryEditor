#ifndef ST_VIEW_MODEL_H
#define ST_VIEW_MODEL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "model/SEResourceModel.h"
#include "GridTilePickerModel.h"
#include "TilePickerListModel.h"

class STViewModel : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QQmlListProperty<QString> tiles READ tiles)

public:
    STViewModel(QQmlApplicationEngine& app_engine);
    void setContext(QQmlContext *context);

public slots:
    void cppSlot(const QString &msg);
    void onFileOpen(const QString &path);
    void onPickerSelected(const QString &name);

signals:
    void loadedEvent();

protected:
    QQmlApplicationEngine& engine;
    QQmlContext *context;

    GridTilePickerModel picker_model;
    SEResourceModel resource_model;
    TilePickerListModel picker_list_model;

//    QList<QString> m_tiles;
};

#endif // ST_VIEW_MODEL_H
