import QtQuick 2.12

Rectangle {
    id: compass
    width: 70
    height: 70
    color: "#a1c4fd"
    smooth: true
    radius: 100
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#09203f"
        }

        GradientStop {
            position: 1
            color: "#537895"
        }
    }
    anchors.centerIn: parent

    Image {
        id: shadow
        width: 90
        height: 90
        anchors.centerIn: compass
        source: "qrc:/image/compress.png"
        opacity: 0.8
        rotation: 3
    }


}
