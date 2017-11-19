#ifndef GRIDTILECANVASPROVIDER_H
#define GRIDTILECANVASPROVIDER_H

#include <QQuickImageProvider>

class GridTileCanvasProvider : public QQuickImageProvider
{
public:
    GridTileCanvasProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // GRIDTILECANVASPROVIDER_H
