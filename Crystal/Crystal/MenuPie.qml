import QtQuick 2.0
import QtQuick.Controls 2.13

Rectangle {
    id: recMove
    width: 100

    Button {
        id: btn_right
        width: 34
        height: 34
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 0
        display: AbstractButton.IconOnly
        rotation: 180
        icon.source : "qrc:/Resources/chevron.png"
        icon.width : _iconSize
        icon.height : _iconSize
        icon.color : hovered ? _colorHover : _colorIcon
        background: Rectangle{
            color:_colorRec
            radius: _radius * 10
        }
    }

    Button {
        id: btn_up
        width: 34
        height: 34
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        display: AbstractButton.IconOnly
        rotation: 90
        icon.source : "qrc:/Resources/chevron.png"
        icon.width : _iconSize
        icon.height : _iconSize
        icon.color : hovered ? _colorHover : _colorIcon
        background: Rectangle{
            color:_colorRec
            radius: _radius * 10
        }
    }

    Button {
        id: btn_left
        width: 34
        height: 34
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        display: AbstractButton.IconOnly
        icon.source : "qrc:/Resources/chevron.png"
        icon.width : _iconSize
        icon.height : _iconSize
        icon.color : hovered ? _colorHover : _colorIcon
        background: Rectangle{
            color:_colorRec
            radius: _radius * 10
        }
    }

    Button {
        id: btn_down
        width: 34
        height: 34
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 0
        display: AbstractButton.IconOnly
        rotation: -90
        icon.source : "qrc:/Resources/chevron.png"
        icon.width : _iconSize
        icon.height : _iconSize
        icon.color : hovered ? _colorHover : _colorIcon
        background: Rectangle{
            color:_colorRec
            radius: _radius * 10
        }
    }
}
