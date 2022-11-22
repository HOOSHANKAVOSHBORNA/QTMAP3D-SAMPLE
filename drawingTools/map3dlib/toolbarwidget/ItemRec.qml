import QtQuick 2.0
import QtQuick.Layouts 1.12

Rectangle {
    id: rectangle
    property string category
    property var name:"item"
    property string icon :"qrc:/res/icon/puzzle.png"
    property bool  check: false
    property bool checkable
    width: 191
    height: 22
    color:"transparent"
    Layout.alignment: Qt.AlignHCenter
    Image {

        width: 20
        height: 20
        anchors.verticalCenter: parent.verticalCenter
        id:image
        anchors.left: parent.left
        anchors.leftMargin: 5
        source:icon
    }

    Text {
        id:txt
        anchors.left: image.right
        anchors.leftMargin: 8
        text : String(name)
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width - image.width
        //horizontalAlignment: Text.AlignHCenter
        font.pointSize: 10
        color: "white"
    }
    MouseArea{
        anchors.fill : parent
        hoverEnabled: true
        onEntered:{
            txt.font.bold =true
        }
        onExited: {
            txt.font.bold =false
        }

        onClicked: {
            //NamePlugin.onGetItemClicked(category,name,check)

            if(checkable){
                if(!check){
                    rectangle.border.width = 1;
                    rectangle.border.color = "#006eFF";
                    txt.color = "#006eFF"
                    check = true
                    rectangle.radius =5
                    NamePlugin.onGetItemClicked(category,name,check)

                }else{
                    rectangle.border.width = 0;
                    rectangle.border.color = "transparent";
                    check =false
                    rectangle.radius =0
                    txt.color = "white"
                    NamePlugin.onGetItemClicked(category,name,check)
                }
            }else{
                NamePlugin.onGetItemClicked(category,name,check)
            }

        }
    }
}
