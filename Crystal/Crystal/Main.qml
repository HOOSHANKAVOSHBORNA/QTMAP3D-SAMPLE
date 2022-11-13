
import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import Crystal 1.0

CrystalWindow {
    id: wnd
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    property real widgetsPositionFactor: 1.0
    property bool swv: true

    onClicked: function() {
        if (wnd.swv === true) {
            widgetsShowAnimation.stop();
            widgetsHideAnimation.start();
            wnd.swv = false;
        } else {
            widgetsHideAnimation.stop();
            widgetsShowAnimation.start();
            wnd.swv = true;
        }
    }

    PropertyAnimation {
        id: widgetsShowAnimation
        target: wnd
        property: "widgetsPositionFactor"
        from: wnd.widgetsPositionFactor
        to: 1.0
        duration: 250 * Math.abs(1.0 - wnd.widgetsPositionFactor)

        easing.type: Easing.OutQuint
    }
    PropertyAnimation {
        id: widgetsHideAnimation
        target: wnd
        property: "widgetsPositionFactor"
        from: wnd.widgetsPositionFactor
        to: 0.0
        duration: 250 * Math.abs(wnd.widgetsPositionFactor)

        easing.type: Easing.OutQuint

    }

    MenuWidget {
        anchors.horizontalCenter: parent.horizontalCenter

        y: (-height - 20) + (wnd.widgetsPositionFactor * (height + 40))

        width: implicitWidth
        height: implicitHeight
    }

}
