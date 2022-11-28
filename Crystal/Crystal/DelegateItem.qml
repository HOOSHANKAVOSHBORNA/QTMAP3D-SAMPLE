import QtQuick 2.0
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.0
Item {
    readonly property int round: 5
    property bool _checked: false
    signal itemClicked(string item_name, string category_name);
    signal changeCheckable(bool check)
    id :delegateItem
    //width: 200
    //height: 230
    clip: true
    Rectangle {
        id: container
        color: itemColor
        anchors.top: rectangle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 200
        border.color: "black"
        z : 1
        radius: round
        opacity: 0.6
        ScrollView {
            id: scroller
            anchors.bottomMargin:2
            anchors.topMargin: 2
            anchors.fill: container
            contentHeight: columnLayout.implicitHeight + 10
            clip : true
            Column {
                id :columnLayout
                width: scroller.width -10
                //height: 150
                anchors.top: parent.top
                anchors.topMargin: 4
                anchors.left: parent.left
                anchors.leftMargin: 4
                spacing: 2
                Repeater {
                    clip: true
                    id: repeater
                    model: categoryModel
                    delegate: Button{
                        id:subbutton
                        width: columnLayout.width - margin
                        height: 30
                        text: itemName
                        hoverEnabled: true
                        display: AbstractButton.TextBesideIcon
                        icon.source: itemIcon
                        icon.width: 16
                        icon.height: 16

                        onClicked: function() {
                                if (itemCheckable)
                                    if (!_checked){
                                        _checked = true
                                        delegateItem.changeCheckable(_checked)
                                    }
                                    else{
                                        _checked = false
                                        delegateItem.changeCheckable(_checked)
                                     }
                            delegateItem.itemClicked(itemName, categoryName);
                        }
                        contentItem:Item {
                            Row{
                                spacing: 5
                                Image {
                                    id: img
                                    source: subbutton.icon.source
                                    width: subbutton.icon.width
                                    height: subbutton.icon.height
                                    anchors.verticalCenter: parent.verticalCenter
                                    ColorOverlay{
                                        id:layeColor
                                        source:img
                                        anchors.fill: img
                                        color: subbutton.hovered || _checked ? _colorHover : "#FFFFFF"
                                    }
                                }


                                Text {
                                    id:subtxt
                                    text: subbutton.text
                                    font: subbutton.font
                                    color: subbutton.hovered || _checked  ? _colorHover: "#FFFFFF"
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    elide: Text.ElideRight
                                }
                            }
                        }


                        background: Rectangle {
                            color:  _colorRec
                            border.color: subbutton.down ? _colorHover : "black"
                            border.width: 1
                            radius: 2
                        }

                    }
                }
            }
        }


    }
    Rectangle {
        id: rectangle
        color: itemColor
        opacity: 0.8
        width: parent.width
        height: 30
        radius: round

        Text {
            id: txt
            color: button.hovered ? _colorHover : "white"
            text: categoryName
            font.wordSpacing: 0.9
            font.weight: Font.Normal
            style: Text.Normal
            font.capitalization: Font.MixedCase
            font.bold: false
            font.pointSize: 10
            font.family: "Times New Roman"
            styleColor: "#dbadad"
            textFormat: Text.PlainText
            horizontalAlignment: Text.AlignLeft
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
        }

        Button {
            id: button
            state: "close"
            width: 28
            height: 28
            text: qsTr("Button")
            clip: true
            hoverEnabled: true
            checkable: true
            focusPolicy: Qt.ClickFocus
            autoRepeat: false
            flat: true
            display: AbstractButton.IconOnly
            highlighted: true
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 5
            rotation: -90
            icon.source: "qrc:/Resources/chevron.png"
            icon.width:  28
            icon.height:   28
            icon.color : hovered ? _colorHover: "white"

            background: Rectangle{
                color: button.hovered ? "transparent" : "transparent"
                border.color: button.hovered ? _colorHover: "transparent"
                border.width: 1
                radius: 5


            }

            onToggled: {

                if (checked){
                    button.rotation = 180
                    container.height = 200
                    delegateItem.height = 230

                }
                else{
                    button.rotation = -90
                    delegateItem.height = 30
                    container.height = 0
                }
            }
        }
    }

}

/*##^##
Designer {
    D{i:3;anchors_height:190;anchors_width:150}
}
##^##*/
