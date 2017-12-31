import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.2

GridView {
    id: view
    /* Padding : 1 (*2) */
    cellWidth: picker_model.tileWidth + 2
    cellHeight: picker_model.tileHeight + 2
    flickableDirection: Flickable.VerticalFlick
    keyNavigationEnabled: true
    focus: true
    highlightFollowsCurrentItem: false

    signal activated(string msg)

    /* Export functions */
    function append() {
        view.model.value = 16
    }

    model: picker_model
    highlight: Component {
        id: highlight
        Rectangle {
            width: view.cellWidth; height: view.cellHeight
            // color: "red"
            radius: 5
            x: (view.currentItem) ? view.currentItem.x : 0
            y: (view.currentItem) ? view.currentItem.y : 0
            z: 1
            color: "transparent"
            border.color: "red"
            border.width: 3
            Behavior on x { SmoothedAnimation { velocity: 2500 } }
            Behavior on y { SmoothedAnimation { velocity: 2500 } }
        }
    }
    delegate: Item {
        Column {
            Rectangle {
                id: rect
                width: picker_model.tileWidth
                height: picker_model.tileHeight
                // colorCode
                color: 'transparent'
                border.color: 'transparent'
                border.width: 0
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    id: marea
                    anchors.fill: parent
                    onClicked: {
                        //console.log("Clicked index: ["+view.currentIndex+"]")
                        view.currentIndex = index
                        view.activated(view.currentIndex)
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
                    cache: false /* This property should be set */
                    verticalAlignment: Image.AlignTop
                    horizontalAlignment: Image.AlignLeft
                    fillMode: Image.Pad

                    onSourceChanged: {
                        view.cellWidth = picker_model.tileWidth + 2
                        view.cellHeight = picker_model.tileHeight + 2
                    }
                }

                Rectangle {
                    id: border_rect
                    width: picker_model.tileWidth
                    height: picker_model.tileHeight
                    opacity: 0.5
                    color: "transparent"
                    border.color: "transparent"
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
    // handle clicks on empty area within the grid.
    // this adds an element below the grid items but on the grid's flickable surface
    // (so it won't have mouse events stolen by the grid)
    flickableChildren: MouseArea {
        anchors.fill: parent
        onClicked: view.currentIndex = -1
    }

    /* KeyBindings */
    Keys.onReturnPressed: {
        // console.log("Picked index: ["+view.currentIndex+"]")
        view.activated(view.currentIndex)
    }
    Keys.onEnterPressed: {
        // On Keypad side
        // console.log("Picked index: ["+view.currentIndex+"]")
        view.activated(view.currentIndex)
    }
}
