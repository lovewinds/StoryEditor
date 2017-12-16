import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0

ApplicationWindow {
    visible: true
    width: 1024
    height: 576
    title: qsTr("Story Editor")

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Open..."
                onTriggered: {
                    console.log("Open a file !")
                    fileDialog.visible = true
                }
            }
            MenuItem {
                text: "Close"
                onTriggered: console.log("Close !")
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a project file"
        folder: shortcuts.home + "/source/StoryEditor/resource"
        visible: false
        nameFilters: [ "XML project file (*.xml)", "All file (*)" ]
        onAccepted: {
            /* Cache option should be turned off. Otherwise, it won't be updated */
            main_form.gridTileCanvasTableView.is_cached = false

            // Notice file opened
            main_form.fileOpen(fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: {
            //visible = true
        }
    }

    MainForm {
        id: main_form
        anchors.fill: parent

        //signal qmlSignal(string msg)
        signal fileOpen(string path)
        signal pickerSelected(string name)

        Component.onCompleted: {
            /* Propagate signals */
            console.log("MainForm completed. connecting signals...")

            picker_view.activated.connect(test)
            object_tree_view.pressAndHold.connect(dragged)
            //qmlSignal.connect(on_win_signal)
            combo_tile.activated.connect(on_changed_picker_list)

            picker_view.model.tileCountChanged.connect(onTilePickerChanged)
        }

        function on_load_finished() {
            console.log("Loading finished !")
            /* Turn cache option on Canvas to enhance speed of dynamic canvas resize */
            main_form.gridTileCanvasTableView.is_cached = true
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

        function on_win_signal(msg) {
            //qmlSignal(msg)
        }

        function on_changed_picker_list(index) {
            console.log(combo_tile.textAt(index))

            pickerSelected(combo_tile.textAt(index))
        }

        function onTilePickerChanged()
        {
            console.log('Picker model changed !')
            region_grid.width = picker_view.model.horizontalTileCount * (picker_view.model.tileWidth + 2) + 6
        }
    }
}
