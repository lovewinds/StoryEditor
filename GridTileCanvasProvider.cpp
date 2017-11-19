#include "GridTileCanvasProvider.h"

QPixmap GridTileCanvasProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    //int idx = id.toInt();
    int width = 40;
    int height = 40;
    QStringList position = id.split(":");

    if (position.size() != 2) {
        qDebug("Unexpected id");
        return QPixmap();
    }

    //qDebug("Not loaded yet");
    //return QPixmap();

    if (size)
        *size = QSize(width, height);

    QImage img_org;
    QImage img_dst;
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    if (img_org.load(":/TEST7B.bmp"))
    {
        int idx_row = position[1].toInt();
        int idx_col = position[0].toInt();
        /*
        qDebug("[Pixmap] row: %d / %d, col %d / %d",
               idx_row, rows,
               idx_col, cols);
        */

        img_dst = img_org.copy(idx_col * 40, idx_row * 40, width, height);
        //qDebug("[Pixmap] QImage dst : [%d, %d]", idx_row * 40, idx_col * 40);
    } else {
        qDebug("[Pixmap] Failed to load image !");
    }

    pixmap = pixmap.fromImage(img_dst);
    //qDebug("[Pixmap] Requested width/height : [%d, %d]", pixmap.width(), pixmap.height());
    //qDebug("[Pixmap] Requested ID: ["+id.toLatin1()+"]");

    return pixmap;
}
