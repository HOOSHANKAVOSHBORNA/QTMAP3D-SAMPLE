
import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    id:rootItem
    width: 380
    height: 80
    readonly property int _iconSize: 32
    readonly property int _margin: 10
    readonly property int _radius: 10
    readonly property color _colorRec: "#88000000"
    readonly property color _colorHover: "#E0E000"
    readonly property color _colorIcon: "#FFFFFF"
    Rectangle {
        id: rootRec
        color: "transparent"
        anchors.fill: parent
        Button {
            id: home
            width: 38
            height: 38
            anchors.top: parent.top
            anchors.topMargin: 0
            hoverEnabled: true
            display: AbstractButton.IconOnly
            anchors.left: parent.left
            anchors.leftMargin: _margin
            icon.source : "qrc:/Resources/home-r.png"
            icon.width : _iconSize
            icon.height : _iconSize
            icon.color : hovered ? _colorHover : _colorIcon
            background: Rectangle{
                radius: 10
                color: _colorRec
            }
        }

        MenuPie{
            id: recMove
            width: 100
            anchors.left: home.right
            anchors.leftMargin: _margin
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: "transparent"
        }

        Button {
            id: positive
            width: rootItem.height /2 - 2
            height: rootItem.height /2 - 2
            anchors.leftMargin: _margin
            anchors.left: recRotation.right
            anchors.top: parent.top
            anchors.topMargin: 1
            icon.source : "qrc:/Resources/zoomin-r.png"
            icon.width : _iconSize
            icon.height : _iconSize
            icon.color : hovered ? _colorHover : _colorIcon
            background:Rectangle {
                color:_colorRec
                radius: _radius
            }
        }

        Button {
            id: negative
            width: rootItem.height /2 - 2
            height: rootItem.height /2 - 2
            text: qsTr("Button")
            anchors.leftMargin: _margin
            display: AbstractButton.IconOnly
            anchors.left: recRotation.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            icon.source : "qrc:/Resources/zoomout-r.png"
            icon.width : _iconSize
            icon.height : _iconSize
            icon.color : hovered ? _colorHover : _colorIcon
            background:Rectangle {
                color:_colorRec
                radius: _radius
            }
        }
        MenuPie{
            id: recRotation
            width: 100
            radius: _radius
            anchors.left: recMove.right
            anchors.leftMargin: _margin
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            color: "transparent"

        }


        Button {
            id: project
            width: 38
            height: 38
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: _margin
            display: AbstractButton.IconOnly
            anchors.left: parent.left
            icon.source : "qrc:/Resources/geocentric.png"
            icon.width : _iconSize
            icon.height : _iconSize
            icon.color : hovered ? _colorHover : _colorIcon
            background: Rectangle{
                radius: _radius
                color: _colorRec
            }
        }
    }

}

/*##^##
Designer {
    D{i:4;anchors_x:8;anchors_y:64}D{i:6;anchors_y:18}D{i:5;anchors_y:18}D{i:7;anchors_y:"-8"}
D{i:9;anchors_width:24;anchors_x:9}D{i:11;anchors_width:24;anchors_y:"-8"}D{i:1;anchors_height:200;anchors_width:200;anchors_x:8;anchors_y:0}
}
##^##*/
