import QtQuick 2.0
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.0
Item {
    readonly property int round: 5
    signal itemClicked(string item_name, string category_name);
    signal changeCheckable(bool check)
    id :delegateItem
    clip: true
    Rectangle {
        id: container
        color: _colorRec
        anchors.top: rectangle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        radius: round
        opacity: 0.7
        border.color: "black"
        border.width: 1

        Column {
            id :columnLayout
            //anchors.fill : parent
            width: scroller.width -10
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
            spacing: 2
            Repeater {
                //clip: true
                id: repeater
                model: categoryModel
                delegate: Button{
                    checked: false
                    id:subbutton
                    width: columnLayout.width - margin
                    height: 30
                    text: itemName
                    hoverEnabled: true
                    display: AbstractButton.TextBesideIcon
                    icon.source: itemIcon
                    icon.width: 24
                    checkable: itemCheckable
                    icon.height: 24
                    font.family: _fontFamily
                    font.pointSize: _fontPointSize - 1
                    opacity: 1
                    onClicked: function() {
                        delegateItem.changeCheckable(checked)
                        delegateItem.itemClicked(itemName, categoryName);
                    }

                    contentItem:Item {
                        Row{
                            anchors.fill: parent
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
                                    color: hovered || checked ? (pressed ? _colorPresed: _colorHover) :
                                                                (pressed ? _colorHover : "#FFFFFF");
                                }
                            }


                            Text {
                                id:subtxt
                                text: subbutton.text
                                font.family: subbutton.font.family
                                font.pointSize:  subbutton.font.pointSize
                                color: hovered || checked  ? (pressed ? _colorPresed: _colorHover) :
                                                             (pressed ? _colorHover : "#FFFFFF");
                                anchors.verticalCenter: parent.verticalCenter
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                elide: Text.ElideRight
                                opacity: 1
                            }
                        }
                    }


                    background: Rectangle {
                        color:  "transparent"
                        //border.color: hovered || checked  ? (pressed ? _colorPresed: _colorHover) :
                        //(pressed ? _colorHover : "transparent");
                        //border.width: 1
                        radius: _radius
                        opacity: 1
                    }

                }
            }
        }
    }
    Button {
        id: rectangle
        text: categoryName
        opacity: 0.8
        width: parent.width
        height: 30
        hoverEnabled: true
        checkable: true
        display: AbstractButton.TextBesideIcon
        icon.source: "qrc:/Resources/chevron.png"
        icon.width:  16
        icon.height:   16

        icon.color : hovered ? (pressed ? _colorPresed: _colorHover) :
                               (pressed ? _colorHover : "#FFFFFF");
        onToggled: {
            if (checked){
                img1.rotation = 180
                container.height += columnLayout.implicitHeight + widgetsMargis
                delegateItem.height += columnLayout.implicitHeight + widgetsMargis

            }
            else{
                img1.rotation = -90
                delegateItem.height = 30
                container.height = 0
            }
        }

        background: Rectangle {
            color:  _colorRec
            //border.color: rectangle.hovered  ? (rectangle.pressed ? _colorPresed: _colorHover) :
            //(rectangle.pressed ? _colorHover : "transparent");
            //border.width: 0
            radius: _radius
            opacity: 1
        }
        contentItem: Item {

            Row{
                Text {
                    id: txt
                    color: rectangle.hovered ? (rectangle.pressed ? _colorPresed: _colorHover) :
                                               (rectangle.pressed ? _colorHover : "#FFFFFF");
                    text: rectangle.text
                    width : rectangle.width - 30
                    font.wordSpacing: 0.9
                    font.pointSize: _fontPointSize
                    font.family: _fontFamily
                    textFormat: Text.PlainText
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    opacity: 1

                }
                Image {
                    id: img1
                    source: rectangle.icon.source
                    width: rectangle.icon.width
                    height: rectangle.icon.height
                    anchors.verticalCenter: parent.verticalCenter
                    rotation: -90
                    ColorOverlay{
                        id:layeColor1
                        source:img1
                        anchors.fill: img1
                        color: rectangle.hovered  ? (rectangle.pressed ? _colorPresed: _colorHover) :
                                                    (rectangle.pressed ? _colorHover : "#FFFFFF");
                    }
                }

            }
        }

    }

}


