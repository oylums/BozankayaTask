// ReceiverDialog.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: popup
    modal: true
    focus: true
    width: 320
    height: 220
    padding: 20

    property string ip: ""
    property int port: 0
    signal startReceiver(string ip, int port)

    anchors.centerIn: Overlay.overlay

    background: Rectangle {
        color: "#eaf4ff"
        border.color: "#3399cc"
        border.width: 1
        radius: 12
    }

    Column {
        anchors.centerIn: parent
        spacing: 14
        width: parent.width - 40

        TextField {
            placeholderText: "Receiver IP"
            text: ip
            onTextChanged: popup.ip = text
            width: parent.width
        }

        TextField {
            placeholderText: "Receiver Port"
            inputMethodHints: Qt.ImhDigitsOnly
            text: port > 0 ? port.toString() : ""
            onTextChanged: popup.port = parseInt(text)
            width: parent.width
        }

        Button {
            text: "Receiver Başlat"
            width: parent.width
            onClicked: {
                if (popup.ip && popup.port > 0) {
                    popup.startReceiver(popup.ip, popup.port)
                    popup.close()
                } else {
                    console.log("IP ya da port geçersiz.")
                }
            }
        }
    }
}
