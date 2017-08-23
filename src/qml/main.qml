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

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        spacing: 5

        Rectangle {
            color: "lightblue"
            radius: 10.0
            width: 300
            height: listViewLocalities.height

            ListView {
                id: listViewLocalities
                width: 100
                height: 200

                highlight: Rectangle {
                    color: 'grey'
                    radius: 5
                }
                focus: true
                flickableDirection: Flickable.AutoFlickDirection

                delegate: Component {
                    Rectangle {
                        id: wrapperLocalities
                        width: localityInfo.width
                        height: localityInfo.height
                        color: ListView.isCurrentItem ? "black" : "white"
                        Text {
                            id: localityInfo
                            text: f_name + "(id: " + f_id + ", description: " + f_description + ")"
                            color: wrapperLocalities.ListView.isCurrentItem ? "white" : "black"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: listViewLocalities.currentIndex = index
                        }
                    }
                }
            }}
        Rectangle { color: "gold"; radius: 10.0
            width: 300; height: listViewMilkPoints.height
            ListView {
                id: listViewMilkPoints
                width: 100
                height: 200

                highlight: Rectangle {
                    color: 'grey'
                    radius: 5
                }
                focus: true
                flickableDirection: Flickable.AutoFlickDirection

                delegate: Component {
                    Rectangle {
                        id: wrapperMilkPoints
                        width: milkPointInfo.width
                        height: milkPointInfo.height
                        color: ListView.isCurrentItem ? "black" : "white"
                        Text {
                            id: milkPointInfo
                            text: f_name
                            color: wrapperMilkPoints.ListView.isCurrentItem ? "white" : "black"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: listViewMilkPoints.currentIndex = index
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: database
        onDbOpened: {
            listViewLocalities.model = database.localities
            listViewMilkPoints.model = database.milkPoints
        }
    }
}
