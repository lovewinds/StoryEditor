TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    DotTileImageProvider.cpp \
    GridTileCanvasProvider.cpp \
    GridTileCanvasModel.cpp \
    ObjectTreeModel.cpp \
    ObjectTreeItem.cpp \
    CustomTreeData.cpp \
    external/pugixml-1.7/src/pugixml.cpp \
    model/SEMapModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Copy external resource files to output directory
mac {
    BUNDLE = $$OUT_PWD/$$TARGET$$quote(.app)/Contents
    QMAKE_POST_LINK += ditto \"$$PWD/sample_scene.xml\" \"$$BUNDLE/Resources/\";
}
#install_ext_resources.path = $$OUT_PWD
#install_ext_resources.files = $$PWD/*.xml

#INSTALLS += \
#    install_ext_resources

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Header path for external libraries
INCLUDEPATH += $$PWD/external/pugixml-1.7/src

HEADERS += \
    DotTileImageProvider.h \
    GridTileCanvasProvider.h \
    GridTileCanvasModel.h \
    ObjectTreeModel.h \
    ObjectTreeItem.h \
    CustomTreeData.h \
    external/pugixml-1.7/src/pugiconfig.hpp \
    external/pugixml-1.7/src/pugixml.hpp \
    model/SEMapModel.h

#DISTFILES += \
#    sample_scene.xml
