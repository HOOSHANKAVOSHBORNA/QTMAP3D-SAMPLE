import QtQuick 2.0
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Item {
    readonly property int round: 5
    id :delegateItem
    width: 200
    height: container.height + rectangle.height
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
            anchors.bottomMargin: 3
            anchors.topMargin: 2
            anchors.fill: container
            clip : true
            Column {
                id :columnLayout
                width: scroller.width -10
                height: 190
                anchors.top: parent.top
                anchors.topMargin: 4
                anchors.left: parent.left
                anchors.leftMargin: 4
                spacing: 2
                Repeater {
                    clip: true
                    id: repeater
                    model: modeltest.node
                    delegate: Button{
                        id:subbutton
                        width: columnLayout.width - margin
                        height: 30
                        text: "hasan"
                        contentItem: Text {
                                text: subbutton.text
                                font: subbutton.font
                                opacity: enabled ? 1.0 : 0.3
                                color: subbutton.down ? "#9E9E9E " : "#FFFFFF"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                elide: Text.ElideRight
                            }

                            background: Rectangle {
                                implicitWidth: 100
                                implicitHeight: 40
                                opacity: enabled ? 1 : 0.3
                                color: "#212121"
                                border.color: subbutton.down ? "#212121" : "black"
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
            color: "white"
            text: model.nameCategory
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

            icon.source: "qrc:/Resources/down-r.png"
            icon.width:  28
            icon.height:   28
            icon.color :"white"

            background: Rectangle{
                color: button.hovered ? "transparent" : "transparent"
                border.color: button.hovered ? "white" : "transparent"
                border.width: 1
                radius: 5


            }

            onToggled: {

                if (checked){
                    button.rotation =180
                    container.height = 200
                    delegateItem.height = 230

                }
                else{
                    button.rotation = 0
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
