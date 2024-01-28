import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import NavModel 1.0

ListView{
    anchors.fill: parent
    id: theNavLayout
    spacing: 50 // 'b' space between elements
    orientation:  Qt.Vertical
    model: NavModel {}

    delegate: Rectangle {
        color: "yellow"
        border.color: "black"
        border.width: 1
        anchors.left: parent.left
        anchors.right: parent.right

        Text{
            text: display
        }
    }

    ScrollBar.vertical: ScrollBar { }
}
