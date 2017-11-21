import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1024
    height: 576
    title: qsTr("Story Editor")

    MainForm {
        anchors.fill: parent

        Component.onCompleted: {
            gridView.activated.connect(test)
            object_tree_view.pressAndHold.connect(dragged)
        }

        function test(msg) {
            console.log(msg)

            // Adjust row
            gridTileCanvasTableView.model = 10;

            console.log("=== delegate ===")
            console.log(gridTileCanvasTableView.delegate.index)
        }

        function dragged(index) {
            console.log("Drag ["+index+"]")
            object_tree_view.Drag.startDrag()
        }


        function on_clicked_plus(index) {
            console.log("clicked plus")
        }

        function on_clicked_minus(index) {
            console.log("clicked minus")
        }
    }
}
