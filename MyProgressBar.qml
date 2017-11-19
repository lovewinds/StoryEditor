import QtQuick 2.6
import QtQuick.Controls 2.1

ProgressBar {
    id: control
    value: 0.5
    padding: 2

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 6
        color: "#e6e6e6"
        radius: 3
    }

    contentItem: Item {
        implicitWidth: 200
        implicitHeight: 4

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            radius: 2
            color: "#17a81a"
        }
    }
}
