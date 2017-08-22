import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Milk.Settings 1.0
import Milk.Database 1.0

ApplicationWindow {
    id: window
    width: 480
    height: 600
    visible: true

    Component.onCompleted: {
        settings.readSettings()
        if (!settings.main.lastChoosenDb.isEmpty)
            database.openDb(settings.main.lastChoosenDb)
    }


    ListView {
        id: listViewLocalities
        anchors.fill: parent

        highlight: Rectangle {
            color: 'grey'
            radius: 5
        }
        focus: true
        flickableDirection: Flickable.AutoFlickDirection

        delegate: Component {
            Rectangle {
                id: wrapper
                width: localityInfo.width
                height: localityInfo.height
                color: ListView.isCurrentItem ? "black" : "white"
                Text {
                    id: localityInfo
                    text: f_name + "(id: " + f_id + ", description: " + f_description + ")"
                    color: wrapper.ListView.isCurrentItem ? "white" : "black"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: listViewLocalities.currentIndex = index
                }
            }
        }
    }

    Connections {
        target: database
        onDbOpened: {
            listViewLocalities.model = database.localities
        }
    }
}
