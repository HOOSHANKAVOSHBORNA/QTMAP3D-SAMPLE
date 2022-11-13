
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.13

Item {
    id: rootItem
    implicitWidth:  rect.implicitWidth
    implicitHeight: rect.implicitHeight


    property ListModel buttonsModel: ListModel {
        ListElement {
            iconSource: "qrc:///Resources/Settings.png"
            labelText: "Settings"
            clickCallback: function() {
                console.log("Settings clicked!");
            }
        }
        ListElement {
            iconSource: "qrc:///Resources/Toolbox.png"
            labelText: "Toolbox"
            clickCallback: function() {
                console.log("Toolbox clicked!");
            }
        }
        ListElement {
            iconSource: "qrc:///Resources/Layers.png"
            labelText: "Layers"
            clickCallback: function() {
                console.log("Layers clicked!");
            }
        }
    }

    Rectangle {
        id: rect
        anchors.fill: parent
        implicitWidth:  rowLayout.implicitWidth + 40
        implicitHeight: rowLayout.implicitHeight + 15

        color: "#404040"
        radius: height * 0.25

        RowLayout {
            id: rowLayout
            anchors.fill: parent
            anchors.margins: 5
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.topMargin: 10
            spacing: 20

            Repeater {
                model: rootItem.buttonsModel
                delegate: Item {
                    implicitWidth: col.implicitWidth
                    implicitHeight: col.implicitHeight

                    ColumnLayout {
                        id: col
                        Image {
                            id: img
                            Layout.alignment: Qt.AlignCenter
                            Layout.preferredWidth: 24
                            Layout.preferredHeight: 24
                            source: iconSource
                            width: 24
                            height: 24

                        }

                        Label {
                            Layout.alignment: Qt.AlignCenter
                            Layout.preferredWidth: implicitWidth
                            Layout.preferredHeight: implicitHeight
                            text: labelText
                            color: "white"
                            font.family: "Srouce Sans Pro"
                            font.pointSize: 11
                        }
                        visible: false
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: col
                        hoverEnabled: true

                        property bool isMouseOnItem: false

                        onEntered: function() {
                            isMouseOnItem = true;
                        }
                        onExited: function() {
                            isMouseOnItem = false;
                        }

                        onClicked: function() {
                            clickCallback();
                        }
                    }

                    ColorOverlay {
                        anchors.fill: col
                        source: col
                        color: mouseArea.isMouseOnItem ?
                                   (mouseArea.pressed ? "#908000" : "#E0E000") :
                                   (mouseArea.pressed ? "#E0E000" : "#FFFFFF");
                    }
                }
            }
        }
    }
}
