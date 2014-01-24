import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import OpticalFlowTools 1.0

Window {

    OpticalFlowTools {
        id: optflowtools
    }

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
                anchors.bottom: recGraph.top
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: radios.bottom
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
                id: radios
                x: 0
                width: rdMatlab.x + rdMatlab.width + 20
                height: rdMatlab.y + rdMatlab.height + 20
                anchors.top: lblTitle.bottom
                anchors.topMargin: 10
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

            Rectangle {
                id: recGraph
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
                onClicked: optflowtools.onCloseButton()
            }

            Button {
                id: button2
                x: 537
                y: 567
                text: "Start"
                anchors.right: button3.left
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                iconSource: "play.png"
                onClicked: optflowtools.onStartButton(
                               (rdGPU.checked) ? 1
                                               : (rdCPU.checked) ? 2
                                                                 : (rdMatlab.checked) ? 3
                                                                                      : -1
                               )
            }

            Button {
                id: button3
                x: 625
                y: 567
                text: "Button"
                anchors.right: button1.left
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                iconSource: "pause.png"
                onClicked: optflowtools.onPauseButton()
            }

            TextEdit {
                id: txtInput
                y: 570
                width: 180
                height: 20
                text: "out/"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: lblIn.right
                anchors.leftMargin: 10
                font.pixelSize: 12
            }

            TextEdit {
                id: txtOutput
                y: 570
                width: 180
                height: 20
                text: "out/flow/"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: lblOut.right
                anchors.leftMargin: 10
                font.pixelSize: 12
            }

            Label {
                id: lblOut
                y: 570
                width: 25
                height: 21
                color: "#0f5a09"
                text: "Out:"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: txtInput.right
                anchors.leftMargin: 30
            }

            Label {
                id: lblIn
                y: 570
                width: 14
                height: 20
                color: "#0f5a09"
                text: "In:"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            Label {
                id: lblTitle
                x: 369
                y: 10
                color: "#76b900"
                text: "Optical Flow"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 14
                anchors.top: parent.top
                anchors.topMargin: 10
                font.bold: true
        }

        }
}
