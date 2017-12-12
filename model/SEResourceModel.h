#ifndef SEMAPMODEL_H
#define SEMAPMODEL_H

#include <string>
#include <vector>
#include <list>
#include <map>

class SETileSetInfo
{
public:
    SETileSetInfo()
        : width(0), height(0) { };

    int width;
    int height;
    std::string name;
    std::string path;
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
    void getTileSize(std::string name, unsigned int& width, unsigned int& height) const;

protected:
    std::vector<std::vector<int> > m_2dMapVector;
    std::vector<int> splitStringTokens(std::string s, std::string delim = " ");
    std::string makeResourcePath(std::string& path) const;

    /* Name / File Path */
    std::map<std::string, SETileSetInfo> m_image_resources;
};

#endif // SEMAPMODEL_H
