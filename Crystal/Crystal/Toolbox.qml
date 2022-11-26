
import QtQuick 2.13
import Qt.labs.platform 1.1
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13
Item {
    id : rootItem
   readonly property int margin: 5

   signal itemClicked(string item_name, string category_name);

   property var toolboxModel: ListModel {
        id : modeltest
   }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 0

   function addToolboxItem(_name, _category) {
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
       if (category_found === true) {
           const categoryModelCount = toolboxModel.get(category_index).categoryModel.count;
           var item_found = false;
           for (var j = 0; j < categoryModelCount; j++) {
               if (toolboxModel.get(category_index).categoryModel.get(j).itemName === _name) {
                   item_found = true;
                   break;
               }
           }
           if (item_found === false) {
               toolboxModel.get(category_index).categoryModel.append({'itemName': _name});
           } else {
               return false;
           }
       } else {
           toolboxModel.append({'categoryName': _category,
                'categoryModel': listModelComponent.createObject(null, {})});
           toolboxModel.get(toolboxModelCount).categoryModel.append({'itemName': _name});
       }

       return true;
   }

   Component.onCompleted: function() {
       addToolboxItem("Amir", "Jafari");
       addToolboxItem("Bagher", "Roodsarabi");
       addToolboxItem("Hasan", "Roodsarabi");
   }
    ScrollView {
        id: scroller
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.topMargin: 5
        width: parent.width
        height: parent.height - margin
        clip : true
        Column {
            id :columnLayout
            anchors.fill: parent
            spacing: 2
            Repeater {
                clip: true
                id: repeater
                model: modeltest
                    delegate: DelegateItem{
                        width: 300
                        height: 30
                        onItemClicked: function(item_name, category_name) {
                            rootItem.itemClicked(item_name, category_name)
                        }
                    }
            }
        }
    }
}



