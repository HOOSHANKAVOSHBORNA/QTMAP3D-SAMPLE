import QtQuick 2.0
import QtQuick.Layouts 1.12

Item {
    property variant varList: NamePlugin.getListNamePlugin()


    onVarListChanged: {
        var component = Qt.createComponent("ItemRec.qml");
        for (var i = 0; i < varList.length; i++){
            if (NamePlugin.getLisCategortPlugin()[i] === "Meature"){
                var object = component.createObject(column);
                object.name =varList[i];
                object.icon = NamePlugin.getListiconPlugin()[i]
                object.category = "Meature"
            }
        }
    }

    property string title: "teste"
    height:column.implicitHeight +6
    width: column.implicitWidth

    ColumnLayout{
        id:column
        anchors.top: parent.top
        anchors.topMargin: 3
        width: laout_back.width



    }
}
