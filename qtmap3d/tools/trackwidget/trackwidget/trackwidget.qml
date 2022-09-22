import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4


Rectangle{
    property bool valuepin: false

    id:root
    width: 200
    color: "transparent"
    Connections{
       target: DetaliObject
       onCloseMenu:{
           if (!valuepin && widgetrack.state === "open"){
           close.start()
           widgetrack.state = "close"
           }
       }
    }

    Connections {
        property  var valueJson
        target: DetaliObject
        onObjectAdded:{
            valueJson =DetaliObject.getInfo()
            var component = Qt.createComponent("PanelItem.qml");
            var object = component.createObject(rootlayer);
            object.title= DetaliObject.getName() + "("+DetaliObject.getType()+")"
            object.name = DetaliObject.getName()
            object.width= laout_back.width
            object.coordinates =String(DetaliObject.getLatitude()+" , "+DetaliObject.getLongitude()+" , "+DetaliObject.getHeight())
        }
    }
    Rectangle{
        id:bar
        height: 23
        width: parent.width
        anchors.top: root.top
        color: "transparent"//
        Rectangle{
            id : backmenu
            width:40
            height: 40
            anchors.right: parent.right
            anchors.rightMargin:3
            anchors.top: parent.top
            anchors.topMargin: 8
            color: "#88000000"
            radius: 10
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if (widgetrack.state === "close"){
                        open.start()
                        widgetrack.state = "open"
                        bar.color = "#282A31"

                        iconpin.visible = true
                        backmenu.color = "transparent"
                        backmenu.anchors.topMargin =-8
                        backmenu.anchors.rightMargin =-5


                    }else{
                        close.start()
                        widgetrack.state = "close"


                    }
                }
            }
            Image {
                id: iconmenu
                source: "qrc:/res/toolbarmenu.png"
                anchors.centerIn: parent
                width:20
                height: 20

            }
        }
        Image {
            id: iconpin
            source: "qrc:/res/unpin.png"
            width:15
            height: 15
            visible: false
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.verticalCenter: parent.verticalCenter
            state: "setpin"
            MouseArea{
                anchors.fill :parent
                onClicked: {
                    if (iconpin.state ==="setpin"){
                        iconpin.source = "qrc:/res/pin.png"
                        iconpin.state = "setunpin"
                        valuepin = true
                        backmenu.enabled = false
                        DetaliObject.onPin(valuepin)
                    }else{
                        iconpin.source = "qrc:/res/unpin.png"
                        iconpin.state = "setpin"
                        valuepin = false
                        backmenu.enabled =true
                        DetaliObject.onPin(valuepin)
                    }

                }
            }
        }

    }
    NumberAnimation{
        id:open
        alwaysRunToEnd: true
        target: widgetrack
        property: "height"
        from:0
        to:800
        duration: 200
    }

    NumberAnimation{
        id:close
        alwaysRunToEnd: true
        target: widgetrack
        property: "height"
        from:800
        to:0
        duration: 200
        onStopped: {
            bar.color = "transparent"
            iconpin.visible = false
            backmenu.color = "#88000000"
            backmenu.anchors.topMargin =8
            backmenu.anchors.rightMargin = 3
        }

    }
    Rectangle{
        id :widgetrack
        state: "close"
        width: parent.width
        clip: true
        height:0//parent.height - bar.height
        anchors.top: bar.bottom
        color: "#282A31"
        border.color: "#282A31"
        border.width: 1
        ScrollView {
            id :laout_back
            anchors.fill: parent

            Column{
                id:rootlayer
                anchors.fill: parent

                spacing: 3

            }
        }
    }
}

