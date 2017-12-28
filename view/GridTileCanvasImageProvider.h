#ifndef GRIDTILECANVASPROVIDER_H
#define GRIDTILECANVASPROVIDER_H

#include <QQuickImageProvider>
#include "model/SEMapModel.h"

class GridTileCanvasImageProvider : public QQuickImageProvider
{
public:
    GridTileCanvasImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap),
          tile_width(40), tile_height(40),
          vertical_tile_count(0), horizontal_tile_count(0),
          model(NULL)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

    void setTileSource(const QString &path, const unsigned int& width, const unsigned int& height);
    void setModel(SEMapModel* model);

    unsigned int tileCount() const;
    unsigned int verticalTileCount() const;
    unsigned int horizontalTileCount() const;

protected:
    QImage img_original;
    unsigned int tile_width;
    unsigned int tile_height;

    unsigned int vertical_tile_count;
    unsigned int horizontal_tile_count;
    unsigned int tile_count;

    SEMapModel* model;
};

#endif // GRIDTILECANVASPROVIDER_H
