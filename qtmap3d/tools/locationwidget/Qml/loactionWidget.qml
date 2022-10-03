import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
Item{
    id: element
    property bool isshow :false
    property bool isshowcurrnt :false
    property bool isshowsave: false
    Connections{
        target: Location
        onSavePosition:{
            var component = Qt.createComponent("RecSavePosition.qml");
            var object = component.createObject(rootlayer);
            object.location = str
            object.lat = x
            object.lon = y

            object.width= laout_back.width - 3
        }
        onChangePosition:{
            currentlocation.text = latitude + " , " + longitude + " , " + altitude
        }
    }

    Rectangle{
        id :locationSave
        width: currentlocation.width + 25
        clip: true
        anchors.bottom: root.top
        anchors.left: save.left
        anchors.leftMargin: 0
        color: "#282A31"
        border.color: "black"
        border.width: 1
        radius: 5
        ScrollView {
            id :laout_back
            anchors.fill: parent

            Column{
                id:rootlayer
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 2
                anchors.rightMargin: 5
                anchors.topMargin: 2
                spacing: 3
            }
        }
    }
    NumberAnimation{
        id:opensave
        alwaysRunToEnd: true
        target: locationSave
        property: "height"
        from:0
        to:200
        duration: 200
        easing.type: Easing.InOutQuad
    }

    NumberAnimation{
        id:closesave
        alwaysRunToEnd: true
        target: locationSave
        property: "height"
        from:200
        to:0
        duration: 200
        easing.type: Easing.InOutQuad
    }
    Addlocation{
        id:add
        width: 100
        height: 0
        anchors.left: root.right
        anchors.leftMargin: -110
        anchors.bottom: root.top

        anchors.bottomMargin: 0

    }
    SavePosition{
        id:save
        width: 100
        height: 0
        anchors.left: parent.left
        anchors.rightMargin: 0
        anchors.bottom: root.top

        anchors.bottomMargin: 0
    }
    NumberAnimation {
        id: opensavelocation
        target: save
        from: 0
        to:40
        property: "height"
        duration: 200
        easing.type: Easing.InOutQuad
    }
    NumberAnimation {
        id: closesavelocation
        target: save
        from: 40
        to:0
        property: "height"
        duration: 200
        easing.type: Easing.InOutQuad
    }
    NumberAnimation {
        id: open
        target: add
        from: 0
        to:80
        property: "height"
        duration: 200
        easing.type: Easing.InOutQuad
    }
    NumberAnimation {
        id: close
        target: add
        from: 80
        to:0
        property: "height"
        duration: 200
        easing.type: Easing.InOutQuad
    }
    Rectangle {
        id : root
        anchors.bottom:  parent.bottom
        width: parent.width
        height: 30
        color: "#88000000"
        radius: 5
        Rectangle{
            id:saverec
            anchors.left: parent.left
            width: 22
            height: 30
            color: "transparent"
            radius: 5
            MouseArea {
                id: mouseArea1
                anchors.fill: parent
                onClicked: {
                    if(!isshowsave){
                        opensavelocation.start()
                        if (isshow){
                            close.start()
                            isshow =false
                        }
                        if (isshowcurrnt){
                            closesave.start()
                            isshowcurrnt = false
                        }

                        isshowsave = true

                        Location.onOpenWidget(isshow , isshowcurrnt  , isshowsave)
                    }else{
                        closesavelocation.start()
                        isshowsave = false
                        Location.onOpenWidget(isshow , isshowcurrnt , isshowsave)
                    }

                }
                onPressed: {
                    imagesave.width +=3
                    imagesave.height+=3
                }
                onReleased: {
                    imagesave.width  -=3
                    imagesave.height -=3
                }
            }
            Image {
                id: imagesave
                anchors.centerIn: parent
                source: "qrc:/res/sortdown.png"
                fillMode: Image.PreserveAspectFit
                rotation: 180
                width: 15
                height: 15
            }
        }

        Rectangle{
            id:backPosition
            anchors.right: rectangle.left
            anchors.rightMargin: 3
            anchors.left: saverec.right
            anchors.leftMargin: 3
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            color: "transparent"
            radius: 5

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.color = "#88000000"
                onExited: parent.color =  "transparent"
                onClicked: {
                    if(!isshowcurrnt){
                        opensave.start()
                        if (isshow){
                            close.start()
                            isshow =false
                        }
                        if (isshowsave){
                            closesavelocation.start()
                            isshowsave = false
                        }
                        isshowcurrnt = true
                        Location.onOpenWidget(isshow, isshowcurrnt, isshowsave)
                    }
                    else{
                        closesave.start()
                        isshowcurrnt = false
                        Location.onOpenWidget(isshow , isshowcurrnt , isshowsave)
                    }
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    id:currentlocation
                    text:"123.23345 , 232.65435  , 1234.55646"
                    font.pixelSize: 10

                }
            }
        }

        Rectangle {
            id: rectangle
            anchors.right: parent.right
            width: 22
            height: 30
            color: "transparent"
            radius: 10
            border.width: 0

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    if(!isshow){
                        open.start()
                        if (isshowcurrnt){

                            closesave.start()
                            isshowcurrnt =false
                        }
                        if (isshowsave){

                            closesavelocation.start()
                            isshowsave = false
                        }
                        isshow = true
                        Location.onOpenWidget(isshow , isshowcurrnt , isshowsave)
                    }else{
                        close.start()
                        isshow = false
                        Location.onOpenWidget(isshow , isshowcurrnt, isshowsave)
                    }

                }
                onPressed: {
                    image.width +=3
                    image.height+=3
                }
                onReleased: {
                    image.width  -=3
                    image.height -=3
                }
            }

            Image {
                id: image
                anchors.centerIn: parent
                source: "qrc:/res/sortdown.png"
                fillMode: Image.PreserveAspectFit
                rotation: 180
                width: 15
                height: 15
            }
        }


    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
