#ifndef SEMAPMODEL_H
#define SEMAPMODEL_H

#include <string>
#include <vector>
#include <list>
#include <map>

class SEMapInfo
{

};

class SEResourceModel
{
public:
    explicit SEResourceModel();
    ~SEResourceModel() {
    }

    void openResourceData(std::string path);

    std::string getTilePath(std::string name) const;
    std::list<std::string> getTileList() const;

protected:
    std::vector<std::vector<int> > m_2dMapVector;
    std::vector<int> splitStringTokens(std::string s, std::string delim = " ");
    std::string makeResourcePath(std::string& path) const;

    /* Name / File Path */
    std::map<std::string, std::string> m_image_resources;
};

#endif // SEMAPMODEL_H
