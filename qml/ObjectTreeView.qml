import QtQuick 2.0
import QtQuick.Controls 1.4
Column {
    width: parent.width
    height: parent.height
    property alias model: columnRepeater.model
    Repeater {
        id: columnRepeater
        delegate: testTreeView
    }
    Component {
        id: testTreeView
        Column {
            width: parent.width
            Item {
                id: infoRow
                width: parent.width
                height: childrenRect.height
                property bool expanded: false
                MouseArea {
                    anchors.fill: parent
                    onClicked: infoRow.expanded = !infoRow.expanded
                    enabled: modelData.children ? true : false
                }
                Text {
                    anchors {
                        left: parent.left
                        top: parent.top
                        margins: 5
                    }
                    font.pointSize: 12
                    visible: parent.visible
                    color: 'white'
                    text: modelData.label
                }
                Text {
                    font.pointSize: 12
                    visible: infoRow.visible
                    color: 'blue'
                    text: modelData.value
                    anchors {
                        top: parent.top
                        right: parent.right
                        margins: 5
                    }
                }
            }
            ListView {
                width: parent.width
                height: childrenRect.height
                visible: opacity > 0
                opacity: infoRow.expanded ? 1 : 0
                delegate: testTreeView
                model: modelData.children ? modelData.children : []
                interactive: false
            }
        }
    }
}
