var component;
var myswitch;

function addSwitch(id) {
    component = Qt.createComponent("myswitch.qml");
    myswitch = component.createObject(id);

    if (myswitch == null) {
        // Error Handling
        console.log("Error creating object");
    }
}

function addButton(id) {
    component = Qt.createComponent("mybutton.qml");
    myswitch = component.createObject(id);

    if (myswitch == null) {
        // Error Handling
        console.log("Error creating object");
    }
}
