import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
Rectangle {
    property string title

    height:120
    width: 200
    color: "#22000000"
    Connections {
        target: DetaliObject
        onChengeCoordinates:{
            if (name === mname){
            element.text = String(latitude + " , " + longitude + " , " + height)
            }
        }
    }
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

            text: coordinates
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
        //color: "#006efa"
        color: "#FFFFFF"
        layer.smooth: true
        width: parent.width -10
        height: parent.height -30
        anchors.top: long_info.bottom
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 5
        radius: 5

        Text {
            id: element3
            color: "#000000"
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
