import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: canDialog
    modal: true
    focus: true
    width: 320
    height: 260

    anchors.centerIn: Overlay.overlay

    signal startClicked(string interfaceName, int bitrate)

    background: Rectangle {
        color: "#f9f9f9"
        radius: 12
        border.color: "#cccccc"
        border.width: 1
    }

    Column {
        anchors.centerIn: parent
        spacing: 14

        Text {
            text: "CAN Settings"
            font.bold: true
            font.pointSize: 16
        }

        ComboBox {
            id: interfaceBox
            width: 200
            model: ["vcan0", "can1"]
            currentIndex: 0
        }

        TextField {
            id: bitrateField
            width: 200
            placeholderText: "Bitrate (örn. 500000)"
            inputMethodHints: Qt.ImhDigitsOnly
            visible: interfaceBox.currentText === "can1"
        }

        Row {
            spacing: 10
            width: parent.width

            Button {
                text: "Start"
                width: parent.width / 2 - 5
                onClicked: {
                    let selectedInterface = interfaceBox.currentText
                    let bitrate = selectedInterface === "can1" ? parseInt(bitrateField.text) : 0
                    canDialog.startClicked(selectedInterface, bitrate)
                    canDialog.close()
                }
            }

            Button {

                text: "Cancel"
                width: parent.width / 2 - 5
                onClicked: canDialog.close()
            }
        }
    }


}
