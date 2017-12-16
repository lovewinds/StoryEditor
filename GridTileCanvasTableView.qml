import QtQuick 2.0
import QtQuick.Controls 2.2

ListView {
    property int num_columns: 6
    property bool is_cached: false

    id: listView
    anchors.fill: parent
    contentWidth: 40 //headerItem.width

    // Disables flickering
    interactive: false
    //flickableDirection: Flickable.HorizontalAndVerticalFlick
/*
    // Currently, header is not required
    header: Row {
        spacing: 1
        function itemAt(index) { return repeater.itemAt(index) }
        Repeater {
            id: repeater
            model: ["#1", "#2", "#3", "#4", "#5"]
            Label {
                text: modelData
                font.bold: true
                font.pixelSize: 16
                padding: 20
                background: Rectangle { color: "silver" }
            }
        }
    }
*/
//    model: 2
    model: gridTileCanvasModel
    delegate: Column {
        id: delegateItem
        property int row: index
        property int row_model: rptr.model
        Row {
            id: test_row
            spacing: 0
            Repeater {
                id: rptr
                //model: (20 - index*2) ? (20-index*2) : 1
                model : num_columns
                ItemDelegate {
                    property int column: index
                    text: qsTr("%1x%2").arg(delegate.row).arg(column)
                    width: 40
                    //width: listView.headerItem.itemAt(column).width

                    MouseArea {
                        id: marea
                        anchors.fill: parent
                        onClicked: {
                            view.currentIndex = index
                            console.log("Clicked index: ["+view.currentIndex+"]")
                            listView.activated("["+view.currentIndex+"]")
                        }
                        onHoveredChanged: {
                            //console.log("Hovered ["+index+"] " + marea.containsMouse)
                            if (marea.containsMouse) {
                                border_rect.border.width = 2
                            } else {
                                border_rect.border.width = 0
                            }
                        }
                        hoverEnabled: true
                    }

                    Image {
                        id: img
                        source: "image://canvas_tiles/"+column+":"+delegateItem.row
                        width: 40
                        height: 40
                        cache: listView.is_cached /* NOTICE: This property should be turn off. Otherwise it won't updated */
                        verticalAlignment: Image.AlignTop
                        horizontalAlignment: Image.AlignLeft
                        fillMode: Image.Pad
                    }

                    Rectangle {
                        id: border_rect
                        width: 40
                        height: 40
                        color: "transparent"
                        border.color: "red"
                        border.width: 0
                    }
                }
            }
        }
    }

    ScrollIndicator.horizontal: ScrollIndicator { }
    ScrollIndicator.vertical: ScrollIndicator { }

    MouseArea {
        id: multiSelection
        anchors.fill: listView
        acceptedButtons: Qt.LeftButton
        //hoverEnabled: true
        onPositionChanged: {
            if(multiSelection.pressed) {
                if(mouseX >= selectLayer.newX) {
                    selectLayer.width = (mouseX + 10) < (listView.x + listView.width) ? (mouseX - selectLayer.x) : selectLayer.width;
                } else {
                    selectLayer.x = mouseX < listView.x ? listView.x : mouseX;
                    selectLayer.width = selectLayer.newX - selectLayer.x;
                }

                if(mouseY >= selectLayer.newY) {
                    selectLayer.height = (mouseY + 10) < (listView.y + listView.height) ? (mouseY - selectLayer.y) : selectLayer.height;
                } else {
                    selectLayer.y = mouseY < listView.y ? listView.y : mouseY;
                    selectLayer.height = selectLayer.newY - selectLayer.y;
                }
            }
        }

        //onPressAndHold: {
        onPressed: {
            selectLayer.visible = true;
            selectLayer.x = mouseX;
            selectLayer.y = mouseY;
            selectLayer.newX = mouseX;
            selectLayer.newY = mouseY;
            selectLayer.width = 0
            selectLayer.height = 0;
        }
/*
        onPressed: {
            selectLayer.x = 0;
            selectLayer.y = 0;
            selectLayer.newX = 0;
            selectLayer.newY = 0;
            selectLayer.visible = false;
            selectLayer.width = 0;
            selectLayer.height = 0;
        }
*/
        onReleased: {
            console.log(listView.width + " ---- " + selectLayer.width);
        }
    }

    Rectangle {
        id: selectLayer
        property int newX: 0
        property int newY: 0
        height: 0
        width: 0
        x: 0
        y: 0
        visible: false
        color: "#00000000"
        // color: "#d341a5"
        opacity: 0.5
        border {
            width: 2
            color: "#d341a5"
        }
        onHeightChanged: {
            //console.log("Height is changed...");
        }
        // onVisibleChanged: {
        // console.log("visibility is changed...");
        // }
    }
}
