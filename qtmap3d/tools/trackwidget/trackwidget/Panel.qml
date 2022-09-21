import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
Rectangle {


    property string title: "teste"
    height:120
    width: 200
    color: "transparent"
    radius: 10

    Rectangle {
        id: long_info
        color: "transparent"
        radius: 3
        width: parent.width
        height: 20
        anchors.top:parent.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 2

        Text {
            id: element
            color: "#fdfdfd"
            padding:4
            text: qsTr("Text")
            font.family: "Times New Roman"
            font.weight: Font.Normal
            style: Text.Normal
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.fill: parent
            font.pixelSize: 10

        }

    }

    Rectangle {
        id: info
        border.color: "#404142"
        color: "#404142"
        border.width: 0.5
        layer.smooth: true
        layer.enabled: true
        opacity: 0.2
        width: parent.width - 5
        height: parent.height -30

        anchors.top: long_info.bottom
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 2
        radius: 3
        layer.effect: ShaderEffect {
            id: effectSource
            anchors.fill: info

            FastBlur{
                id: blur
                anchors.fill: effectSource
                source: effectSource
                radius: 32
            }
        }
        Text {
            id: element3
            color: "#FFFFFF"
            padding:4
            text: "gkjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjhfhmngklhhhhhhhhhhhhhhhhhhhhhhjbfyufjgghhjftyyyyyyyyyyyyyyyyyyyyyyyfjhf"
            wrapMode: Text.WrapAnywhere
            font.family: "Tahoma"
            horizontalAlignment: Text.AlignLeft
            anchors.fill: parent
            font.pixelSize: 10
        }

    }

}

/*##^##
Designer {
    D{i:2;anchors_x:20;anchors_y:4}D{i:4;anchors_x:20;anchors_y:4}D{i:6;anchors_x:20;anchors_y:4}
D{i:8;anchors_x:63;anchors_y:16}
}
##^##*/
