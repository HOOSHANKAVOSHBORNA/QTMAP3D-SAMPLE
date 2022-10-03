import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    property string location
    property real lat
    property real lon

    id : recsaved
    height: 20
    color: "white"
    radius: 5

    Text {
        text:  location + " (" + lat + "," + lon + ")"
        font.pixelSize: 10
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        color: "black"
    }
    MouseArea{
        anchors.fill: recsaved
        onClicked: {
            Location.onCurrentClicked(location)
        }
        onPressed: {
            recsaved.width +=1
            recsaved.height +=1
        }
        onReleased: {
            recsaved.width -=1
            recsaved.height -=1
        }
    }
}
