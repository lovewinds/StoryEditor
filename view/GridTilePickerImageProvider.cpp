#include "view/GridTilePickerImageProvider.h"
#include <QDebug>

void GridTilePickerImageProvider::setTileSource(const QString &path, const unsigned int& width, const unsigned int& height)
{
    img_original.detach();
    if (false == img_original.load(path))
        qDebug() << "Failed to load image: " << path;
    else
    {
        if (width > 0)
            tile_width = width;
        if (height > 0)
            tile_height = height;

        int row_count = (int)(img_original.width() / tile_width);
        int col_count = (int)(img_original.height() / tile_height);
        tile_count = row_count * col_count;

        qDebug() << "Successfully set : " << path;
        qDebug("  Size : [%d x %d]", img_original.width(), img_original.height());
        qDebug("  Rows [%d], Cols [%d] | Total [%d]", row_count, col_count, tile_count);

        horizontal_tile_count = row_count;
        vertical_tile_count = col_count;
    }
}

unsigned int GridTilePickerImageProvider::tileCount() const
{
    return tile_count;
}

unsigned int GridTilePickerImageProvider::verticalTileCount() const
{
    return vertical_tile_count;
}

unsigned int GridTilePickerImageProvider::horizontalTileCount() const
{
    return horizontal_tile_count;
}

QPixmap GridTilePickerImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int idx = id.toInt();
    int width = tile_width;
    int height = tile_height;

    if (size)
        *size = QSize(width, height);

    if (true == img_original.isNull())
    {
        qDebug("[Pixmap] Not prepared yet");
        return QPixmap();
    }

    QImage img_dst;
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    int row_count = (int)(img_original.width() / width);
    int col_count = (int)(img_original.height() / height);
    int x = (int)(idx % row_count);
    int y = (int)(idx / row_count);

    img_dst = img_original.copy(x * width, y * height, width, height);
    pixmap = pixmap.fromImage(img_dst);

//    qDebug("[Pixmap] Requested ID: [%s] : [%d, %d]", id.toStdString().c_str(), x * width, y * height);
//    qDebug("         Rows [%d], Cols [%d]", row_count, col_count);

    return pixmap;
}
