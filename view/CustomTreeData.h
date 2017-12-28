#ifndef CUSTOMTREEDATA_H
#define CUSTOMTREEDATA_H

#include <QObject>

class CustomTreeData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation NOTIFY indentationChanged)

public:
    explicit CustomTreeData(QObject *parent = 0);
    CustomTreeData(const CustomTreeData &other);
    ~CustomTreeData();

    QString text();
    void setText(QString text);

    int indentation();
    void setIndentation(int indentation);

signals:
    void textChanged();
    void indentationChanged();

private:
    QString myText;
    int myIndentation;
};

Q_DECLARE_METATYPE(CustomTreeData)

#endif // CUSTOMTREEDATA_H
