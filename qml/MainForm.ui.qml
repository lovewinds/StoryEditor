import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: window

    width: 1024
    height: 576
    color: "#25272C"
    property alias object_tree_view: object_tree_view
    property alias gridTileCanvasTableView: gridTileCanvasTableView
    property alias picker_view: picker_view
    property alias combo_tile: combo_tile
    property alias region_grid: region_grid

    signal qmlSignal(string msg)
    signal load_test(string path)

    SplitView {
        id: layout_content
        anchors.fill: parent
        handleDelegate: Rectangle {
            color: '#333333'
            width: 1
        }

        SplitView {
            id: splitView_side
            width: 200
            Layout.minimumWidth: 200
            orientation: Qt.Vertical
            handleDelegate: Rectangle {
                color: '#333333'
                width: 1
            }

            Rectangle {
                id: side_menu_layer
                height: 500
                Layout.fillHeight: true
                Layout.minimumHeight: 100
                color: "#25272c"
                border.width: 0

                Rectangle {
                    id: side_menu_text_box
                    height: 20
                    color: "#2e323b"
                    border.width: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0

                    Text {
                        id: side_menu_text_layer
                        color: "#ffffff"
                        text: qsTr("Layer")
                        font.family: "Verdana"
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        font.pixelSize: 14
                    }
                }

                TreeView {
                    id: object_tree_view
                    anchors.topMargin: 0
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.top: side_menu_text_box.bottom
                    anchors.rightMargin: 0
                    frameVisible: false
                    headerVisible: false
                    backgroundVisible: false
                    model: theModel
                    itemDelegate: ObjectTreeDelegate {
                    }

                    rowDelegate: Rectangle {
                        color: "#25272C"
                    }

                    TableViewColumn {
                        role: "name"
                        title: "Name"
                    }
                }
            }

            Rectangle {
                id: side_menu_object
                height: 200
                Layout.minimumHeight: 200
                color: "#25272c"
                border.width: 0

                Rectangle {
                    id: side_menu_object_text_box
                    height: 20
                    color: "#2e323b"
                    border.width: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0

                    Text {
                        id: side_menu_object_text
                        color: "#ffffff"
                        text: qsTr("Object")
                        font.family: "Verdana"
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        font.pixelSize: 14
                    }
                }
            }
        }

        Rectangle {
            id: region_draw
            color: "#25272c"
            Layout.fillWidth: true

            Rectangle {
                id: menu_draw
                height: 40
                color: "#25272c"
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top

                Rectangle {
                    id: _border_bottom
                    height: 2
                    color: "#333333"
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                }

                Button {
                    id: button_col_plus
                    x: 427
                    y: 8
                    width: 40
                    text: qsTr("+")
                    anchors.right: button_col_minus.left
                    anchors.rightMargin: 10
                }

                Button {
                    id: button_col_minus
                    x: 527
                    y: 8
                    width: 40
                    text: qsTr("-")
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                }

                Button {
                    id: button_signal_test
                    y: 8
                    text: qsTr("signal")
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }

                Button {
                    id: button_signal_load
                    y: 8
                    text: qsTr("Load")
                    anchors.left: button_signal_test.right
                    anchors.leftMargin: 10
                }
            }

            Rectangle {
                id: drawing_area
                color: "#25272c"
                anchors.top: menu_draw.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.topMargin: 0

                GridTileCanvasTableView {
                    id: gridTileCanvasTableView
                    x: 0
                    y: 0
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.top: drawing_area.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.topMargin: 0
                }
            }
        }

        Rectangle {
            id: region_grid
            width: 260
            Layout.minimumWidth: 100
            color: "#25272c"

            Rectangle {
                id: grid_menu
                height: 46
                color: "#2e323b"
                anchors.right: parent.right
                anchors.rightMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: 2
                anchors.top: parent.top
                anchors.topMargin: 0

                Text {
                    id: text1
                    color: "#ffffff"
                    text: qsTr("Tile Picker")
                    font.family: "Verdana"
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    font.pixelSize: 14
                }

                ComboBox {
                    id: combo_tile
                    y: 32
                    height: 22
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    model: tilePickerListModel
                    /*
                    ListModel {
                        id: combo_model
                        ListElement { text: "Banana"; }
                        ListElement { text: "Apple"; }
                        ListElement { text: "Coconut"; }
                    }*/
                }
            }

            GridTilePickerView {
                id: picker_view
                x: 0
                y: 526
                boundsBehavior: Flickable.DragOverBounds
                anchors.rightMargin: 2
                anchors.leftMargin: 2
                anchors.bottomMargin: 0
                anchors.top: grid_menu.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.topMargin: 4
                //color: "#fdebeb"
            }
        }
    }

    Connections {
        target: button_col_plus
        onClicked: gridTileCanvasTableView.num_columns += 1
    }

    Connections {
        target: button_col_minus
        onClicked: gridTileCanvasTableView.num_columns -= 1
    }

    Connections {
        target: button_signal_test
        onClicked: qmlSignal('clicked signal!')
    }

    Connections {
        target: button_signal_load
        onClicked: fileOpen('test')
    }
}
