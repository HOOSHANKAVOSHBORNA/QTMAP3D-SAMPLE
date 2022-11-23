import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
Item {
    id: root
    property bool valuePin: false
    property alias getstart: open
    property alias getstart1: close
    property int space: 3
    property int  tools_btn_width: 30
    property int  tools_btn_height: 32
    height: 70
    width:  80
    Connections{
        target: NamePlugin
        onIsclose:{

            if (!valuePin && back.state === "open" && backmenu.enabled){
                close.start()
                back.state = "close"
                iconname.width = tools_btn_width
                iconname.height = tools_btn_height
            }
        }
        onOnPin:{
            if (t){
                root.height = parent.height

            }else{
                open.start()
                back.state = "open"
            }
        }

        onIsDock:{
            toolbar.height = height - 10
        }
        onChangeSize:{
            if (t){
                root.height = 300
                root.width  = 200
            }

        }

    }
    Rectangle{
        anchors.fill: parent
        //color: "blue"
        id:menu
        x:0
        color: "transparent"
        radius: 10
        //state: "open"

        Rectangle{
            id: back
            height: 23
            //width: 50
            color: "transparent"
            anchors.top:menu.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            state: "close"
            anchors.topMargin: -2
            Rectangle{
                id:backmenu
                anchors.left: parent.left
                anchors.leftMargin: 0
                width: tools_btn_width+18
                height: tools_btn_height+15
                anchors.top: parent.top
                anchors.topMargin: 10
                radius: 30
                color: "#282A31"
                MouseArea{
                    anchors.fill: backmenu
                    id :click
                    onClicked: {

                        if (back.state==="open"){
                            close.start()
                            back.state="close"
                            iconname.width = tools_btn_width
                            iconname.height = tools_btn_height

                            NamePlugin.setSizeWidget(false)
                        }else
                        {
                            open.start()
                            back.state="open"
                            iconname.width = 22
                            iconname.height = 20
                            pin.visible =true
                            back.color = "#282A31"
                            back.width = toolbar.width
                            backmenu.color = "#282A31"
                            backmenu.anchors.topMargin = -12
                            backmenu.anchors.leftMargin= -8
                            NamePlugin.setSizeWidget(true)
                        }
                    }
                }
                Image {
                    id: iconname
                    source: "qrc:/res/icon/toolbarmenu.png"
                    width: tools_btn_width+3
                    height: tools_btn_height
                    anchors.centerIn: parent

                }
            }
            Image {
                id: pin
                visible: false
                source: "qrc:/res/icon/unpin.png"
                width: 15
                height: 15
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.verticalCenter: parent.verticalCenter
                state: "setpin"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if (pin.state ==="setpin"){
                            pin.source = "qrc:/res/icon/pin.png"
                            pin.state = "setunpin"
                            valuePin = true
                            backmenu.enabled = false
                            NamePlugin.onPin(valuePin)

                        }else{
                            pin.source = "qrc:/res/icon/unpin.png"
                            pin.state = "setpin"
                            valuePin = false
                            backmenu.enabled =true
                            NamePlugin.onPin(valuePin)
                            NamePlugin.setSizeWidget(true)
                        }

                    }
                }
            }
        }
        NumberAnimation{
            id:open
            target: toolbar
            property: "height"
            from:0
            to:270
            duration: 200

        }

        NumberAnimation{
            id:close
            target: toolbar
            property: "height"
            from:270
            to:0
            duration: 200
            onStopped: {
                backmenu.color = "#282A31"
                backmenu.anchors.topMargin = 3
                backmenu.anchors.leftMargin = 1
                back.rotation=0

                pin.visible =false
                back.color = "transparent"
            }

        }
        Rectangle{
            id:toolbar
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.top: back.bottom
            anchors.topMargin: 0
            clip : true
            color: "transparent"
            height: 0
            radius: 5
            width: back.width

            ScrollView {
                id :laout_back
                anchors.fill: parent
                clip: true
                width: parent.width
                //ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                Column{
                    id:rootlayer
                    anchors.fill: parent

                    spacing: 0.5

                    PanelItem{
                        title: "File"
                        width: laout_back.width
                        content:Panelfile{}
                    }

                    PanelItem {
                        title: "Draw"
                        width: laout_back.width
                        content:Paneldraw{}
                    }
                    PanelItem {
                        title: "Measures"
                        width: laout_back.width
                        content:Panelmeasure{}
                    }
                    PanelItem {
                        title: "Image"
                        width: laout_back.width
                        content:Panelimage{}
                    }
                    PanelItem {
                        title: "Terrain"
                        width: laout_back.width
                        content:Panelterrain{}
                    }

                    PanelItem {
                        title: "Model"
                        width: laout_back.width
                        content:Panelmodel{}
                    }
                    PanelItem {
                        title: "Feature"
                        width: laout_back.width
                        content:Panelfeature{}
                    }
                    PanelItem{
                        title: "Analyze"
                        width: laout_back.width
                        content:Panelanalyze{}
                    }
                    PanelItem{
                        title: "Effect"
                        width: laout_back.width
                        content:Paneleffect{}
                    }

                }


            }

        }
    }
}

