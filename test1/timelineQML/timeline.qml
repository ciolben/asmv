import Spline 1.0
import QtQuick 2.1
import QtQml.Models 2.1

Item {
    id: container
    property int numHLine: 10
    property int numVLine: 10
//    width: 750
//    height: 350

    MouseArea {
        hoverEnabled: true
        id:mousePos
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        anchors.fill: parent
        property bool drag: false
        onPressed: {
            if (mouse.button == Qt.RightButton) {
                drag = true
            }
        }

        onPositionChanged: if (drag) splineDrawer.mouseOnButtonPressed(mousePos.mouseX,
                                                             mousePos.mouseY)
        onReleased: {
            if (drag) {
                splineDrawer.mouseOnButtonReleased(mouse.x, mouse.y)
                drag = false
            } else if (mouse.button == Qt.LeftButton) {
                splineDrawer.mouseOnClick(mouse.x, mouse.y)
            }
        }

        SplineDrawer {
            //anchors.top: parent
            id: splineDrawer
            z: 1
            width: parent.width
            height: parent.height
            curwidth: width
            curheight: height
        }

        Item {
            id: mouseLine
            width: 1; height: container.height
            x: mousePos.mouseX
            y: 0
            z: 2
            Column {
                spacing: 10
                Repeater {
                    model: mouseLine.height / 10
                    delegate: Rectangle {
                        width: mouseLine.width; height: 5
                        color: Qt.rgba(1,1,1,.5)
                    }
                }
            }
        }

        Rectangle {
            id: currentPositionLine
            width: 1; height: container.height
            color: "#eee814"
            x: splineDrawer.playposition * container.width / splineDrawer.duration
            z: 2
        }

        function computeTime(pos) {
            var time
            var p = pos / container.width
            var h, m, s
            s = splineDrawer.duration * p / 1000
            m = s / 60
            s = Math.floor(s % 60)
            h = Math.floor(m / 60)
            m = Math.floor(m % 60)
            time = h < 10 ? "0" + h : h
            time += ":" + (m < 10 ? "0" + m : m)
            time += ":" + (s < 10 ? "0" + s : s)
            return " " + time
        }

        Text {
            property int playpos: splineDrawer.playposition * container.width / splineDrawer.duration
            id: qml_lblPlay
            color: "#ece914"
            text: parent.computeTime(playpos)
            x: container.width - playpos < 50 ? playpos - 43 : playpos
        }

        Text {
            id: qml_lblInfo
            text: parent.computeTime(mousePos.mouseX)
            x:container.width - mousePos.mouseX < 50 ? mousePos.mouseX - 43 : mousePos.mouseX
            y: parent.height - 2 * height
            z: 2
            color: Qt.rgba(1,1,1,.5)

        }

        Rectangle {
            id: recTimeline
            x: 0
            y: 0
            color: "#4b4949"
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent

            Line {
                id: vline
                orientation: "v"
                rheight: rsize
                rwidth: parent.height
                x: 0
            }

            Line {
                id: hline
                orientation: "h"
                y: parent.height - height
                width: parent.width
                color: colorRed
            }

            Column {
                property int space: parent.height / numHLine;
                y: space
                spacing: space
                Repeater {
                    model: numHLine - 1;
                    delegate: Line {
                        orientation: "h"
                        x: rsize
                        rwidth: parent.parent.width
                    }


                }
            }

            Row {
                property int space: parent.parent.width / numVLine;
                spacing: space
                x: space
                Repeater {
                    model: numVLine - 1
                    delegate: Line {
                        orientation: "v"
                        rheight: rsize
                        rwidth: parent.parent.height - rsize
                    }
                }
            }
        }
    }
}
