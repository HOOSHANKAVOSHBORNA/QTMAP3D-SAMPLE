import QtQuick 2.0
import QtQuick.Controls 2.12
Item {
    width: 70
    height: 70
    Button{
        checkable: true
        checked: false
        hoverEnabled: true
        display: AbstractButton.IconOnly
        anchors.fill: parent
        icon.source: "qrc:/Resources/location.png"
        icon.width: 32
        icon.height: 32
        icon.color: hovered ? (pressed ? _colorPresed: _colorHover) :
                              (pressed ? _colorHover : "#FFFFFF");
        background: Rectangle{
            anchors.fill: parent
            color: _colorRec
            radius: _radius
            opacity: 0.8
        }
        onToggled: {
            if (checked){
                openanimation.running = true
            }else
                closeanimation.running = true
        }
    }


    ParallelAnimation {
        id :openanimation
        running: false
        NumberAnimation { target: gpoint; property: "width"; from:0; to: 200; duration: 1000 }
        NumberAnimation { target: gpoint; property: "height"; from: 0 ;to: 100; duration: 1000 }
    }
    ParallelAnimation {
        id :closeanimation
        running: false
        NumberAnimation { target: gpoint; property: "width"; from:200; to: 0; duration: 1000 }
        NumberAnimation { target: gpoint; property: "height"; from: 100 ;to: 0; duration: 1000 }
    }
}
