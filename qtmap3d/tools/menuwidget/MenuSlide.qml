import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
Rectangle{
    Timer {
        id: timer
    }
    //    function delay(delayTime, cb) {
    //        timer.interval = delayTime;
    //        timer.repeat = false;
    //        timer.triggered.connect(cb);
    //        timer.start();
    //    }
    property alias getstart: open
    property alias getstart1: close
    property int space: 3
    id:menu
    x:- width
    color: "transparent"
    state: "close"
    Rectangle{
        id: back
        width: 23
        height: 23
        radius: 100
        color: "#88000000"
        border.color: "white"
        border.width: 1
        anchors.leftMargin:0
        anchors.left: parent.right
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.5
    Image {

        source: "qrc:/res/right-r.png"
        width: 20
        height: 20
        rotation: 0
        anchors.centerIn: parent
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: back.opacity=1
            onExited: back.opacity=0.5

            onClicked: {
                if (menu.state==="open"){
                    close.start()
                     back.rotation=0
                    menu.state="close"
                    back.anchors.top=undefined
                    back.anchors.verticalCenter=menu.verticalCenter
                    back.anchors.leftMargin=0
                }else
                {
                    open.start()
                    back.rotation=180
                    menu.state="open"
                    back.anchors.verticalCenter=undefined
                    back.anchors.top=menu.top
                    back.anchors.topMargin=4
                    back.anchors.leftMargin=-25
                    back.z=1

                }


            }

        }
    }
}
    NumberAnimation{
        id:open
        target: menu
        property: "x"
        from:- width
        to:0
        duration: 200

    }

    NumberAnimation{
        id:close
        target: menu
        property: "x"
        from:0
        to:-width
        duration: 200

    }
    ScrollView {
        id :laout_back
        anchors.right: parent.right
        anchors.rightMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 3
        clip : true


    Column{
        anchors.fill: parent

        spacing: 0

        Rectangle{
            id : backtools
            width: parent.width
            height: 110
            color: "transparent"
            Column{
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    id:drowbar
                    width: parent.width
                    height: 25
                    color: "#CC000000"
                    Text {
                        id: name
                        text: qsTr("Drow")
                        anchors.centerIn: parent
                        color: "white"
                        anchors.margins: 10
                    }
                }
                Rectangle{
                    width: backtools.width
                    height: backtools.height -25
                    color: "#88000000"
                    Tools{}
                }

            }
        }
        Rectangle{
            id : backtools1
            width: parent.width
            height: 110
            color: "transparent"
            Column{
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    width: parent.width
                    height: 25
                    color: "#CC000000"
                    Text {
                        text: qsTr("measurement")
                        anchors.centerIn: parent
                        color: "white"
                        anchors.margins: 10
                    }
                }
                Rectangle{
                    width: backtools.width
                    height: backtools.height -25
                    color: "#88000000"
                    Tools1{}
                }

            }
        }

//        PanelItem{
//            width: parent.width
//            title :"Drow"
//            content: Tools{}
//        }

        PanelItem {
            title: "Image"
            width: laout_back.width
            content:Panel1{}
        }
        PanelItem {
            title: "Terrain"
            width: laout_back.width
            content:Panel1{}
        }
        PanelItem {
            title: "Meature"
            width: laout_back.width
            content:Panel1{}
        }
        PanelItem {
            title: "Model"
            width: laout_back.width
            content:Panel1{}
        }

    }




}
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
