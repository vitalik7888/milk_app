import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import Milk.Core 1.0
import Milk.Settings 1.0
import Milk.Database 1.0

ApplicationWindow {
    id: appWindow
    title: qsTr("Milk app")
    visible: true

    width: 800
    height: 600
    minimumWidth: 640
    minimumHeight: 480

    menuBar: MilkMenuBar {}

    MessageDialog {
        id: messageDialog

        function showInfo(infoDescription) {
            messageDialog.text = infoDescription
            messageDialog.icon = StandardIcon.Information
            messageDialog.open()
        }

        function showWarning(warningDescription) {
            messageDialog.text = warningDescription
            messageDialog.icon = StandardIcon.Warning
            messageDialog.open()
        }

        function showError(errorDescription) {
            messageDialog.text = errorDescription
            messageDialog.icon = StandardIcon.Critical
            messageDialog.open()
        }
    }

    FileDialog {
        id: fileDialogChooseDb

        title: qsTr("Выберите или создайте базу данных")
        selectMultiple: false

        onAccepted: {
            milkDb.openDb(fileUrl.toString().replace("file://", ""))
        }
    }

    TabView {
        id: tabViewContent
        anchors.fill: parent

        Tab {
            title: qsTr("Расчёты")

            CalcPage {

            }
        }

        Tab {
            title: qsTr("Сдача молока")

            MilkReceptionsPage {

            }
        }
    }

    toolBar: ToolBar {
        height: 20
    }

    Connections {
        target: milkDb.deliverers
        onError: messageDialog.showError(error)
    }
    Connections {
        target: milkDb.localities
        onError: messageDialog.showError(error)
    }
    Connections {
        target: milkDb.milkPoints
        onError: messageDialog.showError(error)
    }
    Connections {
        target: milkDb.milkReception
        onError: messageDialog.showError(error)
    }

    Connections {
        target: milkDb

        onDbOpened: {
            milkSettings.main.lastChoosenDb = milkDb.dbPath
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
