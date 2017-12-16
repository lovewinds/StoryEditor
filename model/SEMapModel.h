#ifndef SEMAPMODEL_H
#define SEMAPMODEL_H

#include <vector>
#include <string>

class SEMapModel
{
public:
    SEMapModel();
    ~SEMapModel() { }

    int getTile(int x, int y) const;
    void setTile(const int x, const int y, int value);

    std::string getMapLayerName() const;
    void loadMap(std::string layer_name, std::vector< std::vector<int> >& map);

protected:
    std::string m_layerName;
    std::vector< std::vector<int> > m_2dMap;
};

#endif // SEMAPMODEL_H
