
import QtQuick 2.13
import Qt.labs.platform 1.1
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13
Item {
    id : root
   readonly property int margin: 5
    ListModel {
        id : modeltest
        ListElement {
            nameCategory : "image"
            listview :[]
        }

        ListElement {
            nameCategory : "image1"
            listview :[]
        }

        ListElement {
            nameCategory : "image2"
            listview :[]
        }

        ListElement {
            nameCategory : "image3"
            listview :[]
        }
        ListElement {
            nameCategory : "image4"
            listview :[]
        }
        ListElement {
            nameCategory : "image5"
            listview :[]
        }

        ListElement {
            nameCategory : "image6"
            listview :[]
        }

        ListElement {
            nameCategory : "image7"
            listview :[]
        }

        ListElement {
            nameCategory : "image8"
            listview :[]
        }
        ListElement {
            nameCategory : "image9"
            listview :[]
        }
        ListElement {
            nameCategory : "image10"
            listview :[]
        }
        ListElement {
            nameCategory : "image11"
            listview :[]
        }
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
                    }
            }
        }
    }
}



