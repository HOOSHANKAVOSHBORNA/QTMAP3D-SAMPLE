
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
    readonly property int _iconSize: 32
    readonly property int _margin: 10
    readonly property int _radius: 10
    readonly property color _colorRec: "#404040"
    readonly property color _colorHover: "#FFCC00"
    readonly property color _colorIcon: "#FFFFFF"

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

    property var toolboxModel: ListModel {

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
        sideWidget.menuWidgetItemClicked(index);
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

    SideWidget {
        id: sideWidget
        x:  -(600 + (widgetsMargis*3)) + (wnd.widgetsPositionFactor * (300 + (widgetsMargis*2.0)))
        y: menuWidget.height + (widgetsMargis * 2.0)
        width: 600 + (widgetsMargis * 2)
        height: parent.height - menuWidget.height - (widgetsMargis * 3)

        sideItemsModel: wnd.sideItemsModel

        onSideItemCreated: function(index, item) {
            switch(index) {
            case 2:
                item.toolboxModel = wnd.toolboxModel;
                item.itemClicked.connect(wnd.toolboxItemClicked);
                break;
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


    function addToolboxItem(_name, _category, _url, _checked,) {
        const toolboxModelCount = toolboxModel.count;
        var category_found = false;
        var category_index = -1;
        for (var i = 0; i < toolboxModelCount; i++) {
            if (toolboxModel.get(i).categoryName === _category) {
                category_found = true;
                category_index = i;
                break;
            }
        }
        if (category_found == true) {
            const categoryModelCount = toolboxModel.get(category_index).categoryModel.count;
            var item_found = false;
            for (var j = 0; j < categoryModelCount; j++) {
                if (toolboxModel.get(category_index).categoryModel.get(j).itemName === _name) {
                    item_found = true;
                    break;
                }
            }
            if (item_found === false) {
                toolboxModel.get(category_index).categoryModel.append({'itemName': _name,
                                                                       'itemIcon' : _url,
                                                                       'itemChecked' : _checked
                                                                      });
            } else {
                return false;
            }
        } else {
            toolboxModel.append({'categoryName': _category,
                                    'categoryModel': listModelComponent.createObject(null, {})});
            toolboxModel.get(toolboxModelCount).categoryModel.append({'itemName': _name,
                                                                         'itemIcon' : _url,
                                                                         'itemChecked' : _checked
                                                                        });
        }

        return true;
    }

    Component {
        id: listModelComponent
        ListModel {
        }
    }

    Component.onCompleted: function() {
        addToolboxItem("Amir",   "Jafari","qrc:/Resources/geocentric.png" ,true );
        addToolboxItem("Bagher", "Roodsarab","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasan",  "Roodsarabi","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasan1",  "Roodsarabi","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasan2",  "Roodsarabi","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasa3",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasa4",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasa5",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasa6",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasa7",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
        addToolboxItem("Hasa8",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
         addToolboxItem("Hasa9",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
         addToolboxItem("Hasa10",  "Roodsara","qrc:/Resources/geocentric.png" ,true);
    }

    NavigationWidget{
        anchors.horizontalCenter: parent.horizontalCenter
        y: wnd.height  - (wnd.widgetsPositionFactor * (height + (widgetsMargis)))
        // slot button
        onBtnHomeClicked: {

        }

        onBtnProjectionClicked: {

        }

        onBtnZoomInClicked: {

        }
        onBtnZoomOutClicked: {

        }
        onBtnUpClicked: {

        }
        onBtnDownClicked: {

        }
        onBtnLeftClicked: {

        }
        onBtnRightClicked: {

        }
        onBtnRotateLeftClicked:{

        }

        onBtnRotateRightClicked:{

        }
        onBtnRotateDownClicked: {

        }
        onBtnRotateUpClicked: {

        }
       ///
    }
    Compass{
        id:compass
        anchors.right: parent.right
        anchors.rightMargin: widgetsMargis
        anchors.bottomMargin: widgetsMargis
        y: wnd.height  - (wnd.widgetsPositionFactor * (height + (widgetsMargis)))
    }
}
