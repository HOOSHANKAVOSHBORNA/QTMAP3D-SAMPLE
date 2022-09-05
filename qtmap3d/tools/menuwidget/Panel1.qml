import QtQuick 2.0
import QtQuick.Layouts 1.12

Item {
    property string title: "teste"
    height:column.implicitHeight +6
    width: column.implicitWidth

    ColumnLayout{
        id:column
        anchors.top: parent.top
        anchors.topMargin: 3
        width: laout_back.width
        ItemRec{

        }
        ItemRec{
            name: "model"
        }
    }

}
