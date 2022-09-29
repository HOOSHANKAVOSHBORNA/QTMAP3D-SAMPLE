import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    property real lat
    property real  lon
    property real alitude
    height: 20
    color: "white"
    radius: 5

    Text {
        text: lat + " , " + lon + " , " + alitude
        font.pixelSize: 10
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        color: "black"
    }
    MouseArea{
        anchors.fill: parenrt
        onClicked: {
            Location.goPosition(lat , lon);
        }
    }
}
