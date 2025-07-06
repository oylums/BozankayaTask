// ReceiverDialog.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: popup
    modal: true
    focus: true
    width: 320
    height: 250
    padding: 20

    property string label: ""
    property string ip: ""
    property int port: 0
    signal startClicked(string ip, int port)
    signal stopClicked()

    anchors.centerIn: Overlay.overlay

    background: Rectangle {
        color: "#f9f9f9"
        radius: 12
        border.color: "#cccccc"
        border.width: 1
    }

    Column {
        anchors.centerIn: parent
        spacing: 14
        width: parent.width - 40

        TextField {
            placeholderText: "IP adresi (239.255.0.1)"
            text: ip
            onTextChanged: popup.ip = text
            width: parent.width
        }

        TextField {
            placeholderText: "Port (45454)"
            inputMethodHints: Qt.ImhDigitsOnly
            text: port > 0 ? port.toString() : ""
            onTextChanged: popup.port = parseInt(text)
            width: parent.width
        }

        Row {
            spacing: 10
            width: parent.width

        Button {
            text: "Start"
            width: parent.width / 2 - 5
            onClicked: {
                if (popup.ip && popup.port > 0) {
                    popup.startClicked(popup.ip, popup.port)
                    popup.close()
                } else {
                    console.log("IP ya da port geçersiz.")
                }
            }
        }

        Button {
            text: "cancel"
            width: parent.width / 2 - 5
            onClicked: {
                 popup.close()
            }
        }
        }
    }
}
