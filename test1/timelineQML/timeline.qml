import Spline 1.0
import QtQuick 2.1

Item {
    id: container
    property int numHLine: 10
    property int numVLine: 10
    width: 750
    height: 350

    SplineDrawer {
        anchors.top: parent
        z: 1
        width: parent.width
        height: parent.height
        curwidth: width
        curheight: height
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
