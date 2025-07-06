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
    signal sendClicked(string canId, string hexData)

    background: Rectangle {
        color: "#f9f9f9"
        radius: 12
        border.color: "#cccccc"
        border.width: 1
    }

    Dialog {
        id: canWarningDialog
        title: "Warning!"
        modal: true
        standardButtons: DialogButtonBox.Ok
        anchors.centerIn: parent

        background: Rectangle {
            color: "#FFF176"
            radius: 8
        }

        contentItem: Text {
            text: "First connect successfully."
            wrapMode: Text.Wrap
            padding: 16
            color: "#212121"
            font.pointSize: 13
            font.bold: true
        }

        onAccepted: {
            console.log("Warning dialog closed.")
        }
    }

    Dialog {
        id: canSendFrameWarningDialog
        title: "Warning!"
        modal: true
        standardButtons: DialogButtonBox.Ok
        anchors.centerIn: parent

        background: Rectangle {
            color: "#FFF176"
            radius: 8
        }

        contentItem: Text {
            text: "Check Id or frame."
            wrapMode: Text.Wrap
            padding: 16
            color: "#212121"
            font.pointSize: 13
            font.bold: true
        }

        onAccepted: {
            console.log("Warning dialog closed.")
        }
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
            width: parent.width
            model: ["vcan0", "can1"]
            currentIndex: 0
        }

        TextField {
            id: bitrateField
            width: parent.width
            placeholderText: "Bitrate ( 500000)"
            inputMethodHints: Qt.ImhDigitsOnly
            visible: interfaceBox.currentText === "can1"
        }

        Row {
            spacing: 10
            width: parent.width

            Button {
                text: qmlGlobal.canController.connected ? "Connected" : "Connect"
                width: parent.width / 2 - 5
                onClicked: {
                    let selectedInterface = interfaceBox.currentText
                    let bitrate = selectedInterface === "can1" ? parseInt(bitrateField.text) : 0
                    canDialog.startClicked(selectedInterface, bitrate)
                }
            }

            Button {
                text: "Exit"
                width: parent.width / 2 - 5
                onClicked: canDialog.close()
            }
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "lightgray"
        }

        Text {
            text: "Send Test Frame"
            font.bold: true
            font.pointSize: 14
        }

        Row {
            spacing: 6

            TextField {
                id: canIdField
                width: 80
                placeholderText: "ID (hex)"
            }

            TextField {
                id: canDataField
                width: 120
                placeholderText: "Data (hex)"
            }

            Button {
                text: "Send"
                onClicked: {
                    if (!qmlGlobal.canController.connected) {
                        console.log("Fİrst connect.")
                        canWarningDialog.open()
                        return
                    }

                    if (canIdField.text.length === 0 || canDataField.text.length === 0) {
                        console.log("ID Error")
                        canSendFrameWarningDialog.open()
                        return
                    }

                    canDialog.sendClicked(canIdField.text, canDataField.text)
                }
            }
        }
    }



}
