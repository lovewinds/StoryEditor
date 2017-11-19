#include "DotTileImageProvider.h"

QPixmap DotTileImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int idx = id.toInt();
    int width = 40;
    int height = 40;

    if (size)
        *size = QSize(width, height);

    QImage img_org;
    QImage img_dst;
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    if (img_org.load(":/TEST7B.bmp"))
    {
        img_dst = img_org.copy(idx * 40, idx * 40, width, height);
        //qDebug("[Pixmap] QImage dst : [%d, %d]", img_dst.width(), img_dst.height());
    } else {
        //qDebug("[Pixmap] Failed to load image !");
    }

/*
    if (idx > 4)
        pixmap.fill(QColor("Green").rgba());
    else
        pixmap.fill(QColor("Red").rgba());
*/
    pixmap = pixmap.fromImage(img_dst);

    //qDebug("[Pixmap] Requested width/height : [%d, %d]", pixmap.width(), pixmap.height());
    //qDebug("[Pixmap] Requested ID: ["+id.toLatin1()+"]");

    return pixmap;
}

QImage DotTileImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 40;
    int height = 40;
    int idx = 0;

    if (size)
        *size = QSize(width, height);

    QImage img_org;
    QImage img_dst;
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    img_org.load(":/TEST7B.bmp");
    img_dst = img_org.copy(0, 0, 20, 20);
    idx = id.toInt();

    qDebug("[Image] Requested width/height : [%d, %d]", pixmap.width(), pixmap.height());
    qDebug("[Image] Requested ID: [%s]", qPrintable(id.toLatin1()));

    return img_dst;
}
