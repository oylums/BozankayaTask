import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import UDP.CONT 1.0
import XML.CONT 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Bozankaya")

    SenderDialog {
            id: senderPopup

            onStartClicked: {
                console.log("Start sender with:", ip, port)
                qmlGlobal.udpController.startSender(ip, port)
            }
            onStopClicked: {
                console.log("stop sender with:", ip, port)
                qmlGlobal.udpController.stopAll()
            }
        }


    FileDialog {
        id: fileDialog
        title: "Bir dosya seçin"
        nameFilters: ["Xml Dosyaları (*.xml)", "JSON (*.json)"]
        onAccepted: {
            const url = Qt.resolvedUrl(selectedFiles[0]);
             const path = url.toString().replace("file://", "");
             console.log("Seçilen dosya:", path);
             qmlGlobal.xmlController.setFilePath(path);
        }
        onRejected: {
            console.log("Kullanıcı dosya seçimini iptal etti.")
        }
    }


    ListView {
        id: listView
        anchors.fill: parent
        model: qmlGlobal.xmlController.values


        delegate: Rectangle {
            width: listView.width
            height: 100
            color: "yellow"
            z: qmlGlobal.zOrderHighlights

            Text {
               anchors.centerIn: parent
               text: modelData
            }

            MouseArea {
                   anchors.fill: parent
                   onClicked: {
                       listView.currentIndex = index
                       senderPopup.label = "Veri: " + modelData
                       senderPopup.ip = "192.168.1.12"
                       senderPopup.port = 45454
                       senderPopup.open()
                   }
               }
        }

        highlight: Rectangle {
            width: listView.width
            height: 100
            z: qmlGlobal.zOrderHighlights
            color: "blue"
        }
    }

    Component.onCompleted: {
        console.log("Global: " + qmlGlobal.zOrderTopMost);
        fileDialog.open();
        listView.currentIndex=2;
        qmlGlobal.xmlController.parseXml()
    }

}
