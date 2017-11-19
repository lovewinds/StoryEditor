import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Window 2.2

GridView {
    id: view

    /* Padding : 1 (*2) */
    cellWidth: 40
    cellHeight: 40

    width: 400
    height: 400

    signal activated(string msg)

    flickableDirection: Flickable.horizontalCenter
    model: gridTileCanvasModel
    delegate: Item {
        Column {
            Rectangle {
                id: rect
                width: 40
                height: 40
                color: '#25272C'
                border.color: '#222222'
                border.width: 1
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    id: marea
                    anchors.fill: parent
                    onClicked: {
                        view.currentIndex = index
                        console.log("Clicked index: ["+view.currentIndex+"]")
                        view.activated("["+view.currentIndex+"]")
                    }
                    onHoveredChanged: {
                        console.log("Hovered ["+index+"] " + marea.containsMouse)
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
                    source: "image://canvas_tiles/"+index
                    width: 40
                    height: 40
                    verticalAlignment: Image.AlignTop
                    horizontalAlignment: Image.AlignLeft
                    fillMode: Image.Pad
                }
                Rectangle {
                    id: border_rect
                    width: 40
                    height: 40
                    color: "transparent"
                    border.color: "#777777"
                    border.width: 0
                }

                states: [
                    State {
                        name: "none"
                        when: (view.currentIndex == -1)
                    },
                    State {
                        name: "selected"
                        when: view.isCurrentItem
                        PropertyChanges {
                            target: rect
                            width: 100
                            height: 100
                            color: 'red'
                        }
                    }
                ]
                transitions: Transition {
                    PropertyAnimation {
                        target: rect
                        properties: "width, height"
                    }
                }
            }
            spacing: 2
        }
    }
    focus: true

    // handle clicks on empty area within the grid.
    // this adds an element below the grid items but on the grid's flickable surface
    // (so it won't have mouse events stolen by the grid)
    flickableChildren: MouseArea {
        anchors.fill: parent
        onClicked: view.currentIndex = -1
    }

    Flickable {
        contentWidth: 160
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }
    }
}
