#include "SEMapModel.h"

SEMapModel::SEMapModel() :
    m_layerName(), m_2dMap()
{

}

int SEMapModel::getTile(int x, int y) const
{
    if (m_2dMap.size() == 0)
        return 0;

    return m_2dMap[y][x];
}

void SEMapModel::setTile(const int x, const int y, int value)
{
    if (m_2dMap.size() == 0)
        if (m_2dMap[y].size() == 0)
            m_2dMap[y][x] = value;
}

std::string SEMapModel::getMapLayerName() const
{
    return m_layerName;
}

void SEMapModel::loadMap(std::string layer_name, std::vector< std::vector<int> >& map)
{
    m_layerName = layer_name;
    m_2dMap = map;
}
