import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    width: 200
    height: 30
    Row{
        id: row
        anchors.fill: parent
        spacing: 5
        Image {
            id: img
            width: 24
            height: 24
            anchors.verticalCenter: parent.verticalCenter
            source: subbutton.icon.source
            verticalAlignment: Image.AlignVCenter
            ColorOverlay{
                id:layeColor
                source:img
                anchors.fill: img
                color: hovered || checked ? (pressed ? _colorPresed: _colorHover) :
                                            (pressed ? _colorHover : "#FFFFFF");
            }
        }


        Text {
            id:subtxt
            text: subbutton.text
            anchors.verticalCenter: parent.verticalCenter
            font.family: subbutton.font.family
            font.pointSize:  subbutton.font.pointSize
            color: hovered || checked  ? (pressed ? _colorPresed: _colorHover) :
                                         (pressed ? _colorHover : "#FFFFFF");
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            opacity: 1
        }
    }
}
