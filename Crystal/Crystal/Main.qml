
import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import Crystal 1.0

CrystalWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")



    RowLayout {
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        height: implicitHeight
        spacing: 10
        anchors.topMargin: 10

        Item {
            Layout.fillWidth: true
        }

        Button {
            Layout.preferredWidth: 30
            Layout.preferredHeight: 30
            width: 30
            height: 30

            text: "\u2630"

            property bool rectIsVisible: false

            onClicked:  function() {
                if (rectIsVisible == true) {
                    showAnimation.stop();
                    hideAnimation.start();
                    rectIsVisible = false;
                } else {
                    hideAnimation.stop();
                    showAnimation.start();
                    rectIsVisible = true;
                }
            }
        }

    }


    Rectangle {

        id: sideRect
        anchors.top: parent.top
        anchors.bottom:  parent.bottom
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        width: 300

        x: -320

        color: "#1144aa"
        opacity: 0.5
        radius: 10

        PropertyAnimation {
            id: hideAnimation
            target: sideRect
            property: "x"
            duration: 300.0 * Math.abs(-320 - sideRect.x) / 340.0
            from: sideRect.x
            to: -320
            loops: 1

            easing.type: Easing.OutQuint
        }

        PropertyAnimation {
            id: showAnimation
            target: sideRect
            property: "x"
            duration: 300.0 * Math.abs(20 - sideRect.x) / 340.0
            from: sideRect.x
            to: 20
            loops: 1

            easing.type: Easing.OutQuint
        }


        ColumnLayout {

            anchors.fill: parent

            Repeater {
                model: 10
                Rectangle {
                    Layout.alignment: Qt.AlignCenter
                    width: 240
                    height: 8
                    color: "white"
                }
            }

        }
    }
}
