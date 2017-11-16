import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Milk.Core 1.0
import Milk.Settings 1.0
import Milk.Database 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Milk app")

    MessageDialog {
        id: messageDialog
    }

    FileDialog {
        id: fileDialogChooseDb
        title: qsTr("Выберите или создайте базу данных")
        selectMultiple: false
        onAccepted: {
            var dbUrl = fileUrl.toString().replace("file://", "")
            milkDb.openDb(dbUrl)
            milkSettings.main.lastChoosenDb = dbUrl
        }
    }

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
        target: milkDb.deliverers

        onError: {
            messageDialog.text = error
            messageDialog.icon = StandardIcon.Warning
            messageDialog.open()
        }
    }

    Component.onCompleted: {
        milkSettings.readSettings();
        if (!milkSettings.main.lastChoosenDb.isEmpty)
            milkDb.openDb(milkSettings.main.lastChoosenDb);
        else {
            fileDialogChooseDb.open()
        }
    }

    Component.onDestruction: {
        milkSettings.writeSettings()
    }
}
