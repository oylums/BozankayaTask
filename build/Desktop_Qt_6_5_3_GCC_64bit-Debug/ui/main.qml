import QtQuick
import QtQuick.Controls

// import QBATask.A

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Bozankaya")

    ListView {
        id: listView
        anchors.fill: parent

        model: 100

        spacing: 4
        delegate: Rectangle {
            width: listView.width
            height: 100
            color: "yellow"


            MouseArea {
                anchors.fill: parent
                onClicked: {
                    listView.currentIndex = index
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
        console.log("Global: " + qmlGlobal.zOrderTopMost)
    }
}
