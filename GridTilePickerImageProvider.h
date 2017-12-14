#ifndef DOTTILEIMAGEPROVIDER_H
#define DOTTILEIMAGEPROVIDER_H

#include <QQuickImageProvider>

class GridTilePickerImageProvider : public QQuickImageProvider
{
public:
    GridTilePickerImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap),
          tile_width(40), tile_height(40),
          vertical_tile_count(0), horizontal_tile_count(0)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

    void setTileSource(const QString &path, const unsigned int& width, const unsigned int& height);

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
};

#endif // DOTTILEIMAGEPROVIDER_H
