import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: popupDialog
    modal: true
    focus: true
    width: 320
    height: 250
    padding: 20

    property string label: ""
    property string ip: qmlGlobal.udpController.lastipadress
    property int port: qmlGlobal.udpController.lastPort
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

        Text {
            text: label
            font.bold: true
            font.pointSize: 16
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }

        TextField {
            placeholderText: "IP adresi (239.255.0.1)"
            text: ip
            onTextChanged: popupDialog.ip = text
            width: parent.width
        }

        TextField {
            placeholderText: "Port (45454)"
            inputMethodHints: Qt.ImhDigitsOnly
            text: port > 0 ? port.toString() : ""
            onTextChanged: popupDialog.port = parseInt(text)
            width: parent.width
        }

        Row {
            spacing: 10
            width: parent.width

            Button {
                text: "Start"
                width: parent.width / 2 - 5
                onClicked: {
                    if (popupDialog.ip && popupDialog.port > 0) {
                        popupDialog.startClicked(popupDialog.ip, popupDialog.port)
                    } else {
                        console.log("Geçersiz IP veya port")
                        popupDialog.close()
                    }
                }
            }

            Button {
                text: "cancel"
                width: parent.width / 2 - 5
                onClicked: {
                    popupDialog.close()
                }
            }
        }
    }
}
