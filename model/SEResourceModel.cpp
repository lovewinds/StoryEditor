#include "model/SEResourceModel.h"

#include <sstream>

#include <pugixml.hpp>
#include <QDebug>
#include <QList>
#include <QCoreApplication>

SEResourceModel::SEResourceModel() : mapModel()
{
}

void SEResourceModel::openResourceData(std::string path)
{
    pugi::xml_document doc;

//    qDebug() << QCoreApplication::applicationDirPath();
//    qDebug() << qPrintable(path.c_str());

//    std::string p;
//    p += QCoreApplication::applicationDirPath().toStdString();
//    p += "/";
//    p += path.c_str();
//    qDebug() << qPrintable(p.c_str());

    if (!doc.load_file(path.c_str())) {
    //if(!doc.load_file(pp.toLatin1().data())) {
        qDebug() << "Failed to open xml scene file !";
        return;
    }


    /* TODO: Foreach for all scenes */
    try {
        std::stringstream s;

        /* Prepare global image resources */
        s.str(std::string());
        s.clear();
        /* Select only base image for tileset */
        s << "/SceneRoot/GlobalResources/ImageResourceGroup/ImageResource[@type='tileset']";
        std::string img_path = s.str();
        pugi::xpath_node_set sel = doc.select_nodes(img_path.c_str());

        for (pugi::xpath_node_set::const_iterator it = sel.begin(); it != sel.end(); ++it) {
            pugi::xpath_node node = *it;
            std::string name(node.node().attribute("name").value());
            std::string image(node.node().attribute("path").value());
            std::string width(node.node().attribute("width").value());
            std::string height(node.node().attribute("height").value());
            std::string tile_width(node.node().attribute("tile_width").value());
            std::string tile_height(node.node().attribute("tile_height").value());

            unsigned int _t_width = 40;
            unsigned int _t_height = 40;
            try {
                _t_width = std::stoi(tile_width);
                _t_height = std::stoi(tile_height);
            }
            catch (std::exception &e) {
                qDebug("%s", e.what());
                qDebug("   Invalid width/height [%s / %s]. Use default size: 40x40", width.c_str(), height.c_str());
            }
/*
            qDebug("[%s] (%sx%s) | %s",
                   name.c_str(),
                   width.c_str(), height.c_str(),
                   image.c_str());
*/
            SETileSetInfo info;
            info.width = _t_width;
            info.height = _t_height;
            info.name = name;
            info.path = makeResourcePath(image);
            m_image_resources.insert( std::map<std::string, SETileSetInfo>::value_type(name, info) );
        }

//        for(auto j = m_image_resources.begin(); j != m_image_resources.end(); j++){
//            qDebug() << "[" << j->first.c_str() << "] " << j->second.c_str();
//        }

        /* Load map data */
        s.str(std::string());
        s.clear();
        s << "/SceneRoot/Scene/Layer[@name='map']/TileMap/Layer";
        std::string map_path = s.str();
        sel = doc.select_nodes(map_path.c_str());
        for (pugi::xpath_node_set::const_iterator it = sel.begin(); it != sel.end(); ++it) {
            pugi::xpath_node node = *it;
            std::string name(node.node().attribute("name").value());
            std::string level(node.node().attribute("level").value());
            std::string source(node.parent().attribute("source").value());
            unsigned int _level = 0;
            if (level.length() > 0)
                _level = std::stoi(level);
            if (_level != 1) continue;

            qDebug("  [%s] -> Layer [%s] (%s)",
                   source.c_str(), name.c_str(), level.c_str());
            for (auto raw_array : node.node().children())
            {
                std::string pcdata(raw_array.text().get());
                //qDebug("   raw : %s", pcdata.c_str());

                /* TODO: Current logic sets each character into grid */
                std::vector<std::string> row_elems;
                std::stringstream ss(pcdata);
                std::string item;

                /* Split each row */
                m_2dMapVector.clear();
                while (std::getline(ss, item, '\n')) {
                    if (item.length() == 0) continue;
                    row_elems.push_back(item);

                    auto a = splitStringTokens(item);
                    m_2dMapVector.push_back(a);
                }
                mapModel.loadMap(source, m_2dMapVector);
            }

//            qDebug("  Raw data:");
//            int idx = 1;
//            for(auto r : m_2dMapVector){
//                std::stringstream ss;
//                for (auto c : r) {
//                    ss << c << " ";
//                }
//                qDebug("  [%d] : %s", idx, ss.str().c_str());
//                idx++;
//            }
        }
    }
    catch (const pugi::xpath_exception& e) {
        qDebug() << "Failed to load map data: " << e.what();
    }
}

std::vector<int> SEResourceModel::splitStringTokens(std::string s, std::string delim)
{
    std::string delimiter = " ";
    std::vector<int> result;

    if (delim.length())
        delimiter = delim;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);

        // Handle token
        if (token.length())
            result.push_back(atoi(token.c_str()));

        s.erase(0, pos + delimiter.length());
    }

    return result;
}

std::string SEResourceModel::makeResourcePath(std::string& path) const
{
    std::string p;
    p += QCoreApplication::applicationDirPath().toStdString();
    p += "/../Resources/";
    p += path;

    return p;
}

std::string SEResourceModel::getTilePath(std::string name) const
{
    SETileSetInfo info;
    std::string result;

    auto it = m_image_resources.find(name);
    if (it != m_image_resources.end())
    {
        info = it->second;
    }
    result = info.path;

    return result;
}

std::list<std::string> SEResourceModel::getTileList() const
{
    std::list<std::string> ls;

    for (auto it = m_image_resources.begin(); it != m_image_resources.end(); ++it)
        ls.push_back(it->first);

    return ls;
}

void SEResourceModel::getTileSize(std::string name, unsigned int& width, unsigned int& height) const
{
    SETileSetInfo info;

    auto it = m_image_resources.find(name);
    if (it != m_image_resources.end())
    {
        info = it->second;
    }

    if (info.width > 0 && info.height > 0)
    {
        width = info.width;
        height = info.height;
    }
}

SEMapModel& SEResourceModel::getMapModel()
{
    return mapModel;
}
