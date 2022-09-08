import QtQuick 2.0
import QtQuick.Layouts 1.12

Item {
    property var items: ["btn1","btn3","btn4","btn4"]

    property string title: "teste"
    height:column.implicitHeight +6
    width: column.implicitWidth

    ColumnLayout{
        id:column
        anchors.top: parent.top
        anchors.topMargin: 3
        width: laout_back.width
        Component.onCompleted: {
            var component = Qt.createComponent("ItemRec.qml");
                    for (var i=0; i<5; i++) {
                        var object = component.createObject(column);
                        object.name =items[i]

                    }


    }

}
}
