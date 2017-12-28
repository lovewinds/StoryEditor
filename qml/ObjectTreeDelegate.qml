import QtQuick 2.0

Item {
    Rectangle {
        id: rect
        anchors.fill: parent
        color: styleData.selected ? '#3BBDE0' : '#25272C'

        Text {
            anchors.fill: parent
            color: 'white'
            elide: styleData.elideMode
            text: "" + styleData.value.text
        }
    }
}
