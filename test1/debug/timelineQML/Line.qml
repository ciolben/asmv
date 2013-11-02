import QtQuick 2.0

Rectangle {
    property string orientation : "h"
    property string colorGreen: "#22881b"
    property string colorRed: "#882020"

    property int rwidth: 1
    property int rheight: 1

    property int rsize: 1

    id: line
    x: 0
    y: 0;
    width : {
        if (orientation == "h") {
            return rwidth
        } else {
            return rheight
        }
    }

    height : {
        if (orientation == "h") {
            return rheight
        } else {
            return rwidth
        }
    }

    color: {
        if (orientation == "h")
             return colorGreen;
        else
            return colorRed;
    }
    radius: 0
    rotation: 0
    transformOrigin: Item.TopLeft
}
