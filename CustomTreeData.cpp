#include "CustomTreeData.h"

CustomTreeData::CustomTreeData(QObject *parent)
    : QObject(parent), myIndentation(0)
{
}

CustomTreeData::CustomTreeData(const CustomTreeData &other)
{
    myText = other.myText;
    myIndentation = other.myIndentation;
}

CustomTreeData::~CustomTreeData()
{
}

QString CustomTreeData::text()
{
    return myText;
}

void CustomTreeData::setText(QString text)
{
    myText = text;
    emit textChanged();
}

int CustomTreeData::indentation()
{
    return myIndentation;
}

void CustomTreeData::setIndentation(int indentation)
{
    myIndentation = indentation;
    emit indentationChanged();
}
