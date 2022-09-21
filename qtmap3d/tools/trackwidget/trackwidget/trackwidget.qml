import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4


Rectangle{
    id:root
    width: 200
    color: "transparent"
    Rectangle{
        id:bar
        height: 23
        width: parent.width
        anchors.top: root.top
        color: "#282A31"
        Image {
            id: iconmenu
            source: "qrc:/res/menu.png"
            width:20
            height: 20
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.verticalCenter: parent.verticalCenter
        }
        Image {
            id: iconpin
            source: "qrc:/res/unpin.png"
            width:15
            height: 15
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.verticalCenter: parent.verticalCenter
        }

    }
    Rectangle{
        width: parent.width
        height:parent.height - bar.height
        anchors.top: bar.bottom
        color: "#282A31"
        ScrollView {
            id :laout_back
            anchors.fill: parent


            Column{
                id:rootlayer
                anchors.fill: parent

                spacing: 3
                PanelItem{
                    title: "File"
                    width: laout_back.width
                }
                PanelItem{
                    title: "File"
                    width: laout_back.width
                }
            }
        }
    }
}

