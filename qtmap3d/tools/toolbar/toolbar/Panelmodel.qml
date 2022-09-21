import QtQuick 2.0
import QtQuick.Layouts 1.12

Item {
    Connections {
        target: NamePlugin
        onItemAdded: {
            var component = Qt.createComponent("ItemRec.qml");

                if (NamePlugin.getCategoryPlugin() === "Model"){
                    var object = component.createObject(column);
                    object.name =String(NamePlugin.getNamePlugin());
                    object.icon = String(NamePlugin.getIconPlugin())
                    object.category = "Model"


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
