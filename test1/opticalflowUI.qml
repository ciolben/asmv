import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0

Window {
    id: window1
        width: 800
        height: 600
       // color: "black"
        title: "For Example 5"

        Item {
            id: bigcontainer
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Item {
                id: images
                width: 800
                anchors.bottom: rectangle1.top
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: group_box1.bottom
                anchors.topMargin: 10
                smooth: true

                Item {
                    id: item_image_1
                    width: (images.width - 4 * 10)  / 3
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 10

                    Label {
                        id: lblImage1
                        x: 0
                        y: 0
                        text: "Frame1"
                    }

                    Image {
                        id: image
                        anchors.topMargin: lblImage1.height
                        anchors.fill: parent
                        source: "car1.jpg"
                    }
                }

                Item {
                    id: item_image_flow
                    y: 0
                    width: (images.width - 4 * 10)  / 3
                    anchors.left: item_image_1.right
                    anchors.leftMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    Label {
                        id: lblImageFlow
                        x: 0
                        y: 0
                        text: "Flow"
                    }

                    Image {
                        id: flow
                        anchors.topMargin: lblImageFlow.height
                        anchors.fill: parent
                        source: "_flowResult2.jpg"
                    }
                }

                Item {
                    id: item_image_2
                    x: 462
                    width: (images.width - 4 * 10)  / 3
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    Label {
                        id: lblImage2
                        x: 0
                        y: 0
                        text: "Frame2"
                    }

                    Image {
                        id: image2
                        anchors.topMargin: lblImage2.height
                        anchors.fill: parent
                        source: "car2.jpg"
                    }
                }
            }

            GroupBox {
                id: group_box1
                x: 0
                width: rdMatlab.x + rdMatlab.width + 20
                height: rdMatlab.y + rdMatlb.height + 20
                anchors.top: text1.bottom
                anchors.topMargin: 0
                checked: false
                checkable: false
                flat: false
                title: "Computation"

                RadioButton {
                    id: rdGPU
                    x: 0
                    y: 0
                    text: "GPU"
                    checked: true

                }

                RadioButton {
                    id: rdCPU
                    x: 100
                    y: 0
                    text: "CPU"
                    enabled: false

                }

                RadioButton {
                    id: rdMatlab
                    x: 207
                    y: 0
                    text: "Matlab"
                    enabled: false
                }

            }

            Text {
                id: text1
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: parent.width
                height: 50
                text: "Optical Flow"
                styleColor: "#c02323"
                font.pixelSize: 20
                color: "#1ea015"
            }

            Rectangle {
                id: rectangle1
                x: 0
                y: 360
                height: 200
                color: "#1c0f0f"
                anchors.bottom: button1.top
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
            }

            Button {
                id: button1
                x: 714
                y: 567
                text: "Close"
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
            }
        }
}
