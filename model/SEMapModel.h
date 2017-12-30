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
    void setTile(const int x, const int y, const int value);
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    std::string getMapLayerName() const;
    void loadMap(std::string layer_name, std::vector< std::vector<int> >& map);
    std::vector< std::vector<int> > getMap(std::string layer_name);

protected:
    std::string m_layerName;
    std::vector< std::vector<int> > m_2dMap;

    unsigned int m_width;
    unsigned int m_height;
};

#endif // SEMAPMODEL_H
