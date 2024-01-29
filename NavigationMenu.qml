import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import NavModel 1.0

ListView{
    anchors.fill: parent
    id: theNavLayout
    objectName: NavMenu
    orientation:  Qt.Vertical
    model: NavModel {}

    signal listViewClicked(index: int, msg: string)

    delegate: Rectangle {
        color: "yellow"
        border.color: "black"
        border.width: 1
        height: 40
        width: parent.width
        anchors.left: parent.left

        Text{
            text: display
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                theNavLayout.currentIndex = index
                theNavLayout.listViewClicked(index, display)
            }
        }
    }

    ScrollBar.vertical: ScrollBar { }
}
