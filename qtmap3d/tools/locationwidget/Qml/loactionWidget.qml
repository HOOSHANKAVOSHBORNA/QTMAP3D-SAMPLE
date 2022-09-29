import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
Item{
    id: element
    property bool isshow :false
    property bool isshowcurrnt :false
    Connections{
        target: Location
        onItemPositionAdd:{
            var component = Qt.createComponent("RecSavePosition.qml");
            var object = component.createObject(rootlayer);
            object.lat= latitude
            object.lon = longitude
            object.alitude = altitude
            object.width= laout_back.width - 3
        }
    }

    Rectangle{
        id :locationSave
        width: currentlocation.width + 25
        clip: true
        anchors.bottom: root.top
        color: "#282A31"
        border.color: "#282A31"
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
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: root.top

        anchors.bottomMargin: 0

    }
    NumberAnimation {
        id: open
        target: add
        from: 0
        to:60
        property: "height"
        duration: 200
        easing.type: Easing.InOutQuad
    }
    NumberAnimation {
        id: close
        target: add
        from: 60
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


        MouseArea{
            anchors.right: rectangle.left
            anchors.rightMargin: 3
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            onClicked: {
                if(!isshowcurrnt){
                    opensave.start()
                    isshowcurrnt = true
                    Location.onOpenWidget(isshow, isshowcurrnt)
                }
                else{
                    closesave.start()
                    isshowcurrnt = false
                    Location.onOpenWidget(isshow , isshowcurrnt)
                }
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                id:currentlocation
                text:"123.23345 , 232.65435  , 1234.55646"
                font.pixelSize: 10

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
                        isshow = true
                        Location.onOpenWidget(isshow , isshowcurrnt)
                    }else{
                        close.start()
                        isshow = false
                        Location.onOpenWidget(isshow , isshowcurrnt)
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
