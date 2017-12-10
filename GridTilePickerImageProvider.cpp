#include "GridTilePickerImageProvider.h"
#include <QDebug>

void GridTilePickerImageProvider::setImageSource(const QString &path)
{
    img_original.detach();
    if (false == img_original.load(path))
        qDebug() << "Failed to load image: " << path;
    else
    {
        qDebug() << "Successfully set : " << path;
        qDebug("  Size : [%d x %d]", img_original.width(), img_original.height());
    }
}

QPixmap GridTilePickerImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int idx = id.toInt();
    int width = 40;
    int height = 40;
    const int cell_width = 40;
    const int cell_height = 40;

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

    int row_count = (int)(img_original.width() / cell_width);
    int col_count = (int)(img_original.height() / cell_height);
    int x = (int)(idx % row_count);
    int y = (int)(idx / row_count);

    img_dst = img_original.copy(x * cell_width, y * cell_height, width, height);
    pixmap = pixmap.fromImage(img_dst);

    qDebug("[Pixmap] Requested ID: [%s] : [%d, %d]", id.toStdString().c_str(), x * cell_width, y * cell_height);
    qDebug("         Rows [%d], Cols [%d]", row_count, col_count);

    return pixmap;
}
