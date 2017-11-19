#ifndef DOTTILEIMAGEPROVIDER_H
#define DOTTILEIMAGEPROVIDER_H

#include <QQuickImageProvider>

class DotTileImageProvider : public QQuickImageProvider
{
public:
    DotTileImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    QImage  requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // DOTTILEIMAGEPROVIDER_H
