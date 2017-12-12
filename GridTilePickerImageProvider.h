#ifndef DOTTILEIMAGEPROVIDER_H
#define DOTTILEIMAGEPROVIDER_H

#include <QQuickImageProvider>

class GridTilePickerImageProvider : public QQuickImageProvider
{
public:
    GridTilePickerImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap),
          tile_width(40), tile_height(40)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

    void setTileSource(const QString &path);
    void setTileSize(const unsigned int& width, const unsigned int& height);

    unsigned int tileCount() const;

protected:
    QImage img_original;
    unsigned int tile_width;
    unsigned int tile_height;

    unsigned int tile_count;
};

#endif // DOTTILEIMAGEPROVIDER_H
