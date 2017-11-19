#ifndef SEMAPMODEL_H
#define SEMAPMODEL_H

#include <string>
#include <vector>

class SEMapInfo
{

};

class SEMapModel
{
public:
    explicit SEMapModel();
    ~SEMapModel() {
    }

    void openMapData(std::string path);

protected:
    std::vector<std::vector<int> > m_2dMapVector;

    std::vector<int> splitStringTokens(std::string s, std::string delim = " ");
};

#endif // SEMAPMODEL_H
