import QtQuick 2.13
import QtQuick.Window 2.13

Rectangle {
    id: name

    visible: true

       // Set the flag directly from QML
    Campass{
        anchors.centerIn: name
    }
}
