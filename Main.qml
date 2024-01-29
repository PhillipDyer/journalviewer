import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Journal Viewer")

    MenuBar {
        id: theMenuBar
        width: parent.width

        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&Open...") }
            Action { text: qsTr("&Export") }
            MenuSeparator {}
            Action {text: qsTr("E&xit") }
        }
    }

    GridLayout {
        anchors.top: theMenuBar.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        id: theGridLayout

        columns: 2
        flow: GridLayout.LeftToRight
        rows: 1

        Rectangle
        {
            color: "green"
            id: navContainer
            anchors.bottom: parent.bottom
            anchors.top : parent.top
            anchors.left: parent.left
            width: 300
            NavigationMenu {
                onListViewClicked: (index, msg) => {
                    journal.updateBootID(msg)
                }
            }
        }

        Rectangle {
            color: "blue"
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: navContainer
            anchors.right: parent.right
            Layout.fillWidth: true
            Layout.fillHeight: true
            JournalGrid {
                id: journal
            }
        }
    }
}
