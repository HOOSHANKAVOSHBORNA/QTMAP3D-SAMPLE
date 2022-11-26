
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
    readonly property color itemColor: "#404040"
    readonly property real widgetsMargis: 10

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

    property var sideItemsModel: ListModel {

        property int currentVisibleIndex: -1

        ListElement {
            title_text: "File"
            icon_url: "qrc:///Resources/File.png"
            side_item_url: "qrc:///File.qml"
        }

        ListElement {
            title_text: "Settings"
            icon_url: "qrc:///Resources/Settings.png"
            side_item_url: "qrc:///Settings.qml"
        }

        ListElement {
            title_text: "Toolbox"
            icon_url: "qrc:///Resources/Toolbox.png"
            side_item_url: "qrc:///Toolbox.qml"
        }
    }

    property var toolBoxModel: ListModel {

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

        for (var i = 0; i < sideItemsModel.count; i++) {
            if(i !== index) {
                sideItemsRepeater.itemAt(i).x = 0;
            }
        }

        if (index == sideItemsModel.currentVisibleIndex) {
            sideItemHideAnimation.target = sideItemsRepeater.itemAt(index);
            sideItemHideAnimation.from = 300 + (widgetsMargis * 2.0);
            sideItemHideAnimation.to = 0;
            sideItemHideAnimation.duration = 200;
            sideItemsModel.currentVisibleIndex = -1;
            sideItemHideAnimation.start();
        } else {
            sideItemShowAnimation.target = sideItemsRepeater.itemAt(index);
            sideItemShowAnimation.from = 0;
            sideItemShowAnimation.to = 300 + (widgetsMargis * 2.0);
            sideItemShowAnimation.duration = 200;
            sideItemsModel.currentVisibleIndex = index;
            sideItemShowAnimation.start();
        }

    }

    MenuWidget {
        id: menuWidget
        anchors.horizontalCenter: parent.horizontalCenter

        y: (-height - widgetsMargis) + (wnd.widgetsPositionFactor * (height + (widgetsMargis * 2.0)))

        width: implicitWidth
        height: implicitHeight

        itemsModel: sideItemsModel
        clickCallback: function(index) {
            wnd.menuWidgetClickCallback(index);
        }
    }

    Item {
        id: sideWidgetContainer
        x:  -(600 + (widgetsMargis*3)) + (wnd.widgetsPositionFactor * (300 + (widgetsMargis*2.0)))
        y: menuWidget.height + (widgetsMargis * 2.0)
        width: 600 + (widgetsMargis * 2)
        height: parent.height - menuWidget.height - (widgetsMargis * 3)


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
            model: sideItemsModel
            delegate: Item {
                anchors.top:parent.top
                anchors.bottom: parent.bottom
                x: 0
                width: 300

                Rectangle {
                    anchors.fill: parent
                    color:"transparent"
//                    color: "#404040"
//                    opacity: 0.8
                    radius: 10

                }

                Loader {
                    anchors.fill: parent
                    source: side_item_url
                    onLoaded: function() {
                        wnd.sideItemCreated(index, item);

                        if (index == 2) {
                            item.toolboxModel = toolBoxModel;
                        }
                    }
                }
            }
        }
    }

    function addSideItem(_title_text, _icon_url, _side_item_url) {
        var new_index = sideItemsModel.count;
        sideItemsModel.append({"title_text": _title_text,
                                "icon_url": _icon_url,
                                "side_item_url": _side_item_url});
        return new_index;
    }


    function addToolboxItem(_name, _category)
    {

    }
}
