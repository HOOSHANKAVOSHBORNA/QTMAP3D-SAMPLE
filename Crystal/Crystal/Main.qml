
import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import Crystal 1.0

CrystalWindow {
    id: wnd
    visible: true
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("Hello World")

    property real widgetsPositionFactor: 1.0
    property bool widgetsVisible: true

    onClicked: function() {
        if (wnd.widgetsVisible === true) {
            widgetsShowAnimation.stop();
            widgetsHideAnimation.start();
            wnd.widgetsVisible = false;
        } else {
            widgetsHideAnimation.stop();
            widgetsShowAnimation.start();
            wnd.widgetsVisible = true;
        }
    }

    ListModel {
        id: uiItemsModel
        property int currentVisibleIndex: -1

        ListElement {
            iconSource: "qrc:///Resources/File.png"
            labelText: "File"
            innerItemUrl: "qrc:///File.qml"
        }
        ListElement {
            iconSource: "qrc:///Resources/Settings.png"
            labelText: "Settings"
            innerItemUrl: "qrc:///Settings.qml"
        }
        ListElement {
            iconSource: "qrc:///Resources/Toolbox.png"
            labelText: "Toolbox"
            innerItemUrl: "qrc:///Toolbox.qml"
        }
        ListElement {
            iconSource: "qrc:///Resources/Layers.png"
            labelText: "Layers"
            innerItemUrl: "qrc:///Layers.qml"
        }
    }

    PropertyAnimation {
        id: widgetsShowAnimation
        target: wnd
        property: "widgetsPositionFactor"
        from: wnd.widgetsPositionFactor
        to: 1.0
        duration: 200 * Math.abs(1.0 - wnd.widgetsPositionFactor)

        easing.type: Easing.OutQuint
    }
    PropertyAnimation {
        id: widgetsHideAnimation
        target: wnd
        property: "widgetsPositionFactor"
        from: wnd.widgetsPositionFactor
        to: 0.0
        duration: 200 * Math.abs(wnd.widgetsPositionFactor)

        easing.type: Easing.InQuint
    }

    function menuWidgetClickCallback(index) {
        sideItemHideAnimation.stop();
        sideItemShowAnimation.stop();

        for (var i = 0; i < uiItemsModel.count; i++) {
            if(i !== index) {
                sideItemsRepeater.itemAt(i).x = 0;
            }
        }

        if (index == uiItemsModel.currentVisibleIndex) {
            sideItemHideAnimation.target = sideItemsRepeater.itemAt(index);
            sideItemHideAnimation.from = 340;
            sideItemHideAnimation.to = 0;
            sideItemHideAnimation.duration = 200;
            uiItemsModel.currentVisibleIndex = -1;
            sideItemHideAnimation.start();
        } else {
            sideItemShowAnimation.target = sideItemsRepeater.itemAt(index);
            sideItemShowAnimation.from = 0;
            sideItemShowAnimation.to = 340;
            sideItemShowAnimation.duration = 200;
            uiItemsModel.currentVisibleIndex = index;
            sideItemShowAnimation.start();
        }

    }

    MenuWidget {
        id: menuWidget
        anchors.horizontalCenter: parent.horizontalCenter

        y: (-height - 20) + (wnd.widgetsPositionFactor * (height + 40))

        width: implicitWidth
        height: implicitHeight

        itemsModel: uiItemsModel
        clickCallback: function(index) {
            wnd.menuWidgetClickCallback(index);
        }
    }

    Item {
        id: sideWidgetContainer
        x:  -660 + (wnd.widgetsPositionFactor * 340)
        y: menuWidget.height + 40
        width: 640
        height: parent.height - menuWidget.height - 60


        PropertyAnimation {
            id: sideItemShowAnimation
            property: 'x'

            easing.type: Easing.OutQuint
        }
        PropertyAnimation {
            id: sideItemHideAnimation
            property: 'x'

            easing.type: Easing.InQuint
        }


        Repeater {
            id: sideItemsRepeater
            model: uiItemsModel
            delegate: Item {
                anchors.top:parent.top
                anchors.bottom: parent.bottom
                x: 0
                width: 300

                Rectangle {
                    anchors.fill: parent
                    color: "#404040"
                    radius: 10
                }

                Loader {
                    anchors.fill: parent
                    source: innerItemUrl
                }
            }
        }
    }



    function createSideWidget(comp, title, icon_url) {
        var cobj = comp.createObject(container, {'anchors.centerIn': container,
                             'width': 400,
                             'height': 400,
                             'opacity': 0.3});
    }
}
