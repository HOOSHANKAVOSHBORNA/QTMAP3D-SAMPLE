import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    property string location
    property real lat
    property real lon

    id : recsaved
    height: 20
    color: "#88000000"
    radius: 5

    Text {
        id :txt
        text:  location + " (" + lat + "," + lon + ")"
        font.pixelSize: 10
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        color: "white"
    }
    MouseArea{
        anchors.fill: recsaved
        hoverEnabled: true
        onClicked: {
            Location.onCurrentClicked(location)
        }

        onEntered : {
            txt.font.bold =true
            recsaved.color = "#88006eff"
        }
        onExited: {
           txt.font.bold =false
            recsaved.color = "#88000000"
        }
    }
}
