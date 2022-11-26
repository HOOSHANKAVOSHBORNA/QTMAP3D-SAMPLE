
import QtQuick 2.13
import QtQuick.Layouts 1.13

Item {
    id: rootItem
    property ListModel toolboxModel

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 0

        Repeater {
            model: rootItem.toolboxModel

            delegate: Rectangle {
                Layout.fillWidth: true
                Layout.minimumHeight: 20 + (categoryModel.count * 20)
                color: "orange"

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    height: implicitHeight
                    text: categoryName
                }

                ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: 0
                    spacing: 0
                    Repeater {
                        model: categoryModel
                        delegate: Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumHeight: 20
                            color:"blue"

                            Text {
                                anchors.centerIn: parent
                                text: itemName
                            }
                        }
                    }
                }
            }
        }


        Item {
            Layout.fillHeight: true
        }
    }
}
