import QtQuick 2.6
import QtQuick.Window 2.2
import MainSettings 1.0
import Settings 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(core.settings.main.lastChoosenDb)
        }
    }
}
