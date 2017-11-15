import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Milk.Core 1.0
import Milk.Settings 1.0
import Milk.Database 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Milk app")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        CalcPage {

        }

        MilkReceptionsPage {

        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Расчёты")
        }
        TabButton {
            text: qsTr("Сдача молока")
        }
    }

    Connections {
        target: db
        onDbOpened: {
        }
    }

    Component.onCompleted: {
        settings.readSettings()
        if (!settings.main.lastChoosenDb.isEmpty)
            db.openDb(settings.main.lastChoosenDb)
    }
}
