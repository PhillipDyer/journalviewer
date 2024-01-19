import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GridLayout{
    anchors.fill: parent
    id: theNavLayout
    columns: 1
    flow: GridLayout.TopToBottom

    Button {
        text: qsTr("button 1")
    }
    Button {
        text: qsTr("button 2")
    }
    Button {
        text: qsTr("button 3")
    }

    ScrollBar.vertical: ScrollBar { }
}
