import QtQuick 2.13
import QtQuick.Window 2.0
 import QtQuick.Controls 2.12
Item {
    width: parent.width
    height: parent.height
//    ButtonMenu{
//        id:button
//        anchors.left: parent.left
//        anchors.leftMargin: 5
//        anchors.verticalCenter: parent .verticalCenter
//        getMouseArea.onClicked: {
//            if(menu.state==="close"){
//            menu.getstart.start();
//            menu.state="open";
//             button.visible=false
//            }
//        }
//    }
    MenuSlide{
        id:menu
        width: parent.width/3
        height: parent.height
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
