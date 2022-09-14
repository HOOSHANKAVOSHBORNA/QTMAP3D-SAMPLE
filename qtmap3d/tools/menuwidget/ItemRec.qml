import QtQuick 2.0
import QtQuick.Layouts 1.12

Rectangle {
    id: rectangle
    property var name:"item"
    property string icon :"qrc:/res/icons8-puzzle-96.png"
   width: 220
   height: 30
   color:"transparent"
   Layout.alignment: Qt.AlignHCenter
   Image {
       width: 24
       height: 24
       anchors.verticalCenter: parent.verticalCenter
       id:image
       source:icon
   }
   Text {
       anchors.left: image.right
       text : String(name)
       anchors.verticalCenter: parent.verticalCenter
       width: parent.width - image.width
       horizontalAlignment: Text.AlignHCenter
       color: "white"
   }
   MouseArea{
       anchors.fill : parent
       onClicked: console.log(name);
   }
}
