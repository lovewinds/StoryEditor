import QtQuick 2.6
import QtQuick.Controls 2.1

BusyIndicator {
    id: control
    property alias anim_rotation: anim_rotation

    contentItem: Item {
        implicitWidth: 64
        implicitHeight: 64

        Item {
            id: item_content
            x: parent.width / 2 - 32
            y: parent.height / 2 - 32
            width: 64
            height: 64
            opacity: control.running ? 1 : 0

            Behavior on opacity {
                OpacityAnimator {
                    duration: 250
                }
            }

            RotationAnimator {
                id: anim_rotation
                target: item_content
                running: control.visible && control.running
                from: 0
                to: 360
                loops: Animation.Infinite
                duration: 1250
            }

            Repeater {
                id: repeater
                model: 6

                Rectangle {
                    x: item_content.width / 2 - width / 2
                    y: item_content.height / 2 - height / 2
                    implicitWidth: 10
                    implicitHeight: 10
                    radius: 5
                    color: "#21be2b"
                    transform: [
                        Translate {
                            y: -Math.min(item_content.width, item_content.height) * 0.5 + 5
                        },
                        Rotation {
                            angle: index / repeater.count * 360
                            origin.x: 5
                            origin.y: 5
                        }
                    ]
                }
            }
        }
    }
}
