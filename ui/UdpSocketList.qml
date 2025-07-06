import QtQuick 2.15
import QtQuick.Controls 2.15


Rectangle {
    color: "grey"

    ListView {
        id: listview
        anchors.fill: parent
        anchors.margins: 1
        spacing: 1
        clip: true
        model: qmlGlobal.udpController.receivers

        delegate: Rectangle {
            height: 40
            width: parent.width
            color: modelData.connected ? "#a5d6a7" : "#ef9a9a"

            Row {
                spacing: 10
                anchors.verticalCenter: parent.verticalCenter
                // Text { text: "IP: " + address }
                // Text { text: "Port: " + port }
                Text { text: index + ' - ' }

                Text { text: modelData.connected ? "✓ Listener Connected" : "Listener Disconnected" }
                Text { text: modelData.ipAddress }
                Text { text: modelData.port }
            }
        }
    }

    Text {
        anchors.centerIn: parent

        z: listview.z + 1

        visible: listview.model.length === 0

        text: "UDP LISTENER CONNECTION NOT EXIST"

        color: "#FFFFFF"
    }
}

