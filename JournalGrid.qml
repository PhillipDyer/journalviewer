import QtQuick
import QtQuick.Controls
import JournalView 1.0

TableView {

    anchors.fill: parent
    columnSpacing: 1
    rowSpacing: 1
    clip: true
    alternatingRows: true
    columnWidthProvider: function(column) {
        return 300
    }

    model: JournalView {}

    ScrollBar.vertical: ScrollBar {}
    ScrollBar.horizontal: ScrollBar {}

    delegate: Rectangle {
        border.width: 1
        border.color: "black"
        Text {
            text: display
        }
    }
}