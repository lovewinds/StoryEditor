#ifndef DOTTILEIMAGEPROVIDER_H
#define DOTTILEIMAGEPROVIDER_H

#include <QQuickImageProvider>

class GridTilePickerImageProvider : public QQuickImageProvider
{
public:
    GridTilePickerImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

    void setImageSource(const QString &path);

protected:
    QImage img_original;
};

#endif // DOTTILEIMAGEPROVIDER_H
