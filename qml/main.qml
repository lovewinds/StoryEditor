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
        signal canvasTileSet(int x, int y, int value)

        Component.onCompleted: {
            /* Propagate signals */
            console.log("MainForm completed. connecting signals...")

            // Picker
            picker_view.activated.connect(on_tile_item_selected)
            picker_view.model.tileCountChanged.connect(onTilePickerChanged)
            combo_tile.activated.connect(on_changed_picker_list)

            // Canvas
            gridTileCanvasTableView.activated.connect(onCanvasActivated)
            gridTileCanvasTableView.changed.connect(onCanvasChanged)

            // Object Tree
            object_tree_view.pressAndHold.connect(dragged)
            //qmlSignal.connect(on_win_signal)

            // View model
            fileOpen.connect(viewModel.onFileOpen)
            qmlSignal.connect(viewModel.cppSlot)
            pickerSelected.connect(viewModel.onPickerSelected)
            canvasTileSet.connect(viewModel.onCanvasChanged)

            viewModel.canvasResized.connect(onCanvasResized)
            viewModel.loadedEvent.connect(on_load_finished)
        }

        function on_load_finished() {
            console.log("Loading finished !")
            /* Turn cache option on Canvas to enhance speed of dynamic canvas resize */
            main_form.gridTileCanvasTableView.is_cached = true
        }

        function on_tile_item_selected(index) {
            console.log("  [Picker] item {"+index+"} selected")
            viewModel.pickTile = index
            gridTileCanvasTableView.pick_tile = index
        }

        function dragged(index) {
            console.log("Drag ["+index+"]")
            object_tree_view.Drag.startDrag()
        }

        function on_test_signal(msg) {
            console.log("  Canvas row count : ", gridTileCanvasTableView.model)
        }

        function on_changed_picker_list(index) {
            console.log(combo_tile.textAt(index))

            pickerSelected(combo_tile.textAt(index))
        }

        function onTilePickerChanged()
        {
            console.log('  [Picker] Model changed !')
            region_grid.width = picker_view.model.horizontalTileCount * (picker_view.model.tileWidth + 2) + 6
        }

        function onCanvasActivated(x, y)
        {
            console.log('  [Canvas] (', x,' x ', y, ') activated !')
        }

        function onCanvasChanged(x, y, value)
        {
            console.log('  [Canvas] (', x,' x ', y, ') changed into [',value,'] !')
            main_form.gridTileCanvasTableView.is_cached = false
            canvasTileSet(x, y, value)
            main_form.gridTileCanvasTableView.is_cached = true
        }

        function onCanvasResized(width, height)
        {
            console.log('Canvas resized to [%d x %d]!', width, height)
            gridTileCanvasTableView.model.value = height;
            gridTileCanvasTableView.num_columns = width;
//            console.log('Canvas resized to [%d ]!', width)
//            console.log('Canvas Resized !')
        }
    }
}
