import QtQuick 2.0

Item {
    property alias marea: mouseArea

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 40
        height: 40
        color: "#d4d4d4"
        border.width: 2
        MouseArea {
            id: mouseArea_rect
            anchors.fill: parent
            hoverEnabled: true

            onHoveredChanged: {
                if (containsMouse)
                    parent.border.color = "#FF0000"
                else
                    parent.border.color = "#000000"
            }
        }
    }
}
