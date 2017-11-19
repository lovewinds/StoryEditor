#include "SEMapModel.h"

#include <sstream>

#include <pugixml.hpp>
#include <QDebug>
#include <QCoreApplication>

SEMapModel::SEMapModel()
{
}

void
SEMapModel::openMapData(std::string path)
{
    pugi::xml_document doc;

    qDebug() << QCoreApplication::applicationDirPath();
    qDebug() << qPrintable(path.c_str());

    std::string p;
    p += QCoreApplication::applicationDirPath().toStdString();
    p += "/";
    p += path.c_str();
    qDebug() << qPrintable(p.c_str());

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
        s << "/SceneRoot/GlobalResources/ImageResourceGroup/ImageResource";
        std::string img_path = s.str();
        pugi::xpath_node_set sel = doc.select_nodes(img_path.c_str());
/*
        for (pugi::xpath_node_set::const_iterator it = sel.begin(); it != sel.end(); ++it) {
            pugi::xpath_node node = *it;
            std::string name(node.node().attribute("name").value());
            std::string image(node.node().attribute("path").value());
            std::string width(node.node().attribute("width").value());
            std::string height(node.node().attribute("height").value());

            qDebug("[%s] (%sx%s) | %s",
                   name.c_str(),
                   width.c_str(), height.c_str(),
                   image.c_str());
        }
*/

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

            qDebug("  Layer [%s] (%s)",
                   name.c_str(), level.c_str());

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
            }

            qDebug("  Raw data:");
            int idx = 1;
            for(auto r : m_2dMapVector){
                std::stringstream ss;
                for (auto c : r) {
                    ss << c << " ";
                }
                qDebug("  [%d] : %s", idx, ss.str().c_str());
                idx++;
            }
        }
    }
    catch (const pugi::xpath_exception& e) {
        qDebug() << "Failed to load map data: " << e.what();
    }
}

std::vector<int> SEMapModel::splitStringTokens(std::string s, std::string delim)
{
    std::string delimiter = " ";
    std::vector<int> result;

    if (delim.length())
        delimiter = delim;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);

        // Handle token
        if (token.length())
            result.push_back(atoi(token.c_str()));

        s.erase(0, pos + delimiter.length());
    }

    return result;
}
