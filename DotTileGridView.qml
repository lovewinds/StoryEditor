import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Window 2.2

GridView {
    id: view

    /* Padding : 1 (*2) */
    cellWidth: 40 + 2
    cellHeight: 40 + 2

    signal activated(string msg)

    flickableDirection: Flickable.VerticalFlick
    model: DotTileGridModel {}
    delegate: Item {
        Column {
            Rectangle {
                id: rect
                width: 40
                height: 40
                color: colorCode
                border.color: 'red'
                border.width: 2
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
                        //console.log("Hovered ["+index+"] " + marea.containsMouse)
                        if (marea.containsMouse) {
                            border_rect.border.width = 2
                            border_rect.border.color = 'red'
                        } else {
                            border_rect.border.width = 0
                            border_rect.border.color = 'black'
                        }
                    }
                    hoverEnabled: true
                }

                Image {
                    id: img
                    source: "image://tiles/"+index
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
                    border.color: "black"
                    border.width: 0
                }

                Text {
                    x: 5
                    text: name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
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
/*
    highlight: Component {
        id: highlight
        Rectangle {
            width: view.cellWidth; height: view.cellHeight
            color: "red"
            radius: 5
            x: view.currentItem.x
            y: view.currentItem.y
            Behavior on x { SmoothedAnimation { velocity: 1000 } }
            Behavior on y { SmoothedAnimation { velocity: 1000 } }
        }
    }
    highlightFollowsCurrentItem: false
*/
    focus: true

    // handle clicks on empty area within the grid.
    // this adds an element below the grid items but on the grid's flickable surface
    // (so it won't have mouse events stolen by the grid)
    flickableChildren: MouseArea {
        anchors.fill: parent
        onClicked: view.currentIndex = -1
    }
}
