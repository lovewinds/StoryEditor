#include <QDebug>
#include "SEMapModel.h"

SEMapModel::SEMapModel() :
    m_layerName(), m_2dMap()
{

}

int SEMapModel::getTile(int x, int y) const
{
    if (x < 0 || y < 0)
        return 0;

    if (m_2dMap.size() == 0)
        return 0;

    return m_2dMap[y][x];
}

void SEMapModel::setTile(const int x, const int y, const int value)
{
    if (m_2dMap.size() == 0)
        if (m_2dMap[y].size() == 0)
            m_2dMap[y][x] = value;

    qDebug() << "Successfully set [" << x << ", " << y << "] with : " << value;
}

std::string SEMapModel::getMapLayerName() const
{
    return m_layerName;
}

unsigned int SEMapModel::getWidth() const
{
    return m_width;
}

unsigned int SEMapModel::getHeight() const
{
    return m_height;
}

void SEMapModel::loadMap(std::string layer_name, std::vector< std::vector<int> >& map)
{
    m_layerName = layer_name;
    m_2dMap = map;

    m_width = map[0].size();
    m_height = map.size();
}
