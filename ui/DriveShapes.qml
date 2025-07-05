
import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id: root
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "#f0f0f0"
    border.color: "gray"
    radius: 5

    Flickable {
        anchors.fill: parent
        contentWidth: 800
        contentHeight: 600
        clip: true

        Item {
            id: canvas
            width: parent.contentWidth
            height: parent.contentHeight

            function drawUI() {
                canvas.destroyAllChildren()

                for (let i = 0; i < qmlGlobal.xmlController.shapes.length; i++) {
                    let shape = qmlGlobal.xmlController.shapes[i]
                    let type = shape.type
                    let id = shape.id
                    let props = ""

                    for (let key in shape) {
                        if (key !== "type" && key !== "id" && key !== "text") {
                            if (!isNaN(Number(shape[key]))) {
                                props += `${key}: ${shape[key]};\n`
                            } else {
                                props += `${key}: "${shape[key]}";\n`
                            }
                        }
                    }

                    let qmlCode = ""

                    if (type === "Text") {
                        qmlCode = `
                            import QtQuick 2.15
                            Text {
                                id: ${id}
                                property alias size: ${id}.font.pointSize
                                text: "${shape.text}"
                                ${props}
                            }
                        `
                    } else if (type === "Image") {
                        qmlCode = `
                            import QtQuick 2.15
                            Image {
                                id: ${id}
                                property alias path: ${id}.source
                                ${props}
                            }
                        `
                    } else if (type === "Line") {
                        qmlCode = `
                            import QtQuick 2.15
                            Canvas {
                                id: ${id}
                                width: ${Math.abs(shape.x2 - shape.x1)}
                                height: ${shape.thickness || 1}
                                x: ${shape.x1}
                                y: ${shape.y1}

                                onPaint: {
                                    let ctx = getContext("2d");
                                    ctx.strokeStyle = "${shape.color}";
                                    ctx.lineWidth = ${shape.thickness || 1};
                                    ctx.beginPath();
                                    ctx.moveTo(0, 0);
                                    ctx.lineTo(${shape.x2 - shape.x1}, 0);
                                    ctx.stroke();
                                }
                            }
                        `
                    } else if (type === "Circle") {
                        qmlCode = `
                            import QtQuick 2.15
                            Rectangle {
                                id: ${id}
                                property alias cx: ${id}.x
                                property alias cy: ${id}.y
                                ${props}
                            }
                        `
                    } else {
                        qmlCode = `
                            import QtQuick 2.15
                            ${type} {
                                id: ${id}
                                ${props}
                            }
                        `
                    }

                    Qt.createQmlObject(qmlCode, canvas, id)
                }
            }

            function destroyAllChildren() {
                let childrenCopy = canvas.children.slice()
                for (let i = 0; i < childrenCopy.length; i++) {
                    childrenCopy[i].destroy()
                }
            }

            Connections {
                target: qmlGlobal.xmlController
                function onShapesChanged() {
                    canvas.drawUI()
                }
            }

            Component.onCompleted: canvas.drawUI()

        }
    }
}
