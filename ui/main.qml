import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import UDP.CONT 1.0
import XML.CONT 1.0
import LOG.MOD  1.0
import CAN.COMM 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Bozankaya Tech")
    color: "black"

    Dialog {
        id: senderReceiverDialog
        title: "Mode"
        modal: true
        standardButtons: Dialog.Cancel
        width: 250
        height: 150

        Column {
            anchors.centerIn: parent
            spacing: 10

            Button {
                text: "Sender"
                onClicked: {
                    senderReceiverDialog.close()
                    senderPopup.open()
                }
            }

            Button {
                text: "Receiver"
                onClicked: {
                    senderReceiverDialog.close()
                    receiverPopup.open()
                }
            }
        }
    }

    SenderDialog {
        id: senderPopup
        onStartClicked: {
            qmlGlobal.udpController.startSender(ip, port)
            senderPopup.close()
        }
        onStopClicked: {
            qmlGlobal.udpController.stopAll()
            senderPopup.close()
        }
    }

    ReceiverDialog {
        id: receiverPopup

        onStartClicked: {
            console.log("Receiver Start:", ip, port)
            qmlGlobal.udpController.startReceiver(ip, port)
        }

        onStopClicked: {
            console.log("Stop Receiver")
            qmlGlobal.udpController.stopAll()
        }
    }

    CanDialog {
        id: canDialog

         onStartClicked: function(m_interface, bitrate) {
           console.log("CAN Interface:", m_interface, "Bitrate:", bitrate)
           qmlGlobal.canController.start(m_interface,bitrate)
       }
         onSendClicked: function(canId, hexData) {
             console.log("CAN Frame → ID:", canId, "Data:", hexData)
             qmlGlobal.canController.sendFrame(canId, hexData)
         }

    }

    FileDialog {
        id: fileDialog
        title: "Choose afile"
        nameFilters: ["Xml Dosyaları (*.xml)", "JSON (*.json)"]
        onAccepted: {
            const url = Qt.resolvedUrl(selectedFiles[0])
            const path = url.toString().replace("file://", "")
            qmlGlobal.xmlController.setFilePath(path)
            qmlGlobal.xmlController.parseXml()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Item {
            Layout.preferredWidth : 8
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Item {
                Layout.preferredWidth : 8
            }

            Rectangle {
                width: 16
                height: 16
                radius: 8
                color: qmlGlobal.udpController.connected ? "green" : "red"
                border.color: "black"
                border.width: 1
            }

            Button {
                text: "Configure UDP"
                onClicked: senderReceiverDialog.open()
            }

            Button {
                text: "Stop"
                onClicked: qmlGlobal.udpController.stopAll()
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                width: 16
                height: 16
                radius: 8
                color: qmlGlobal.canController.connected ? "green" : "red"
                border.color: "black"
                border.width: 1
            }

            Button {
                text: "Configure CAN"
                onClicked: canDialog.open()
            }

            Button {
                text: "Disconnect"
                onClicked: qmlGlobal.canController.stop()
            }

            Item {
                Layout.preferredWidth : 8
            }
        }

        DriveShapes {
            color: "grey"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        UdpSocketList {
            Text {
                anchors.right: parent.right
                id: udpListText
                text: qsTr("UDP RECEIVERS LIST")
                color: "white"
            }
            Layout.fillWidth: true
            Layout.preferredHeight: 100
        }


        Rectangle {
            id: logSection
            Layout.fillWidth: true
            height: 100
            color: "#222"
            border.color: "black"
            radius: 5

            ListView {
                id: logListview
                clip: true
                anchors.fill:parent
                model:qmlGlobal.logModel

                delegate: Rectangle {
                    color: index % 2 == 0 ? "#859144" : "900000"
                    width: logListview.width
                    height: 30

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        color: "#FFFFFF"
                        font.pointSize: 12
                        text: display
                    }

                    Component.onCompleted: logListview.currentIndex = index

                }
            }

        }
    }

    Component.onCompleted: fileDialog.open()

}
