
import QtQuick 2.13
import Qt.labs.platform 1.1
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13

Item {
    id : rootItem

    readonly property int margin: 5
    signal itemClicked(string item_name, string category_name);
    property var toolboxModel


        ScrollView {
            id: scroller
            anchors.fill: parent
            contentHeight: columnLayout.implicitHeight
            //clip : true
            Item {
                id: tmp
                anchors.fill: parent
            }

            Column {
                id :columnLayout
                anchors.fill: parent
                spacing: 2
                Repeater {
                    id: repeater
                    model: rootItem.toolboxModel
                    delegate: DelegateItem{
                        Layout.fillWidth: true
                        width: tmp.width
                        height: 30
                        onItemClicked: function(item_name, category_name) {
                            rootItem.itemClicked(item_name, category_name)
                        }
                    }
                }
            }
        }


}

