
import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: popup
    modal: true
    focus: true
    width: 300
    height: 160
    anchors.centerIn: Overlay.overlay

    background: Rectangle {
        color: "#fff3e0"
        border.color: "#ffaa00"
        border.width: 1
        radius: 10
    }

    Column {
        anchors.centerIn: parent
        spacing: 12

        Text {
            text: "Can özel popup"
            font.bold: true
            font.pointSize: 16
        }

        Button {
            text: "Kapat"
            onClicked: popup.close()
        }
    }
}
