import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import MilkCore 1.0
import Milk.Types 1.0
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
            milkCore.db.openDb(fileUrl.toString().replace("file://", ""))
        }
    }

    TabView {
        id: tabViewContent
        anchors.fill: parent

        Tab {
            title: qsTr("Редактирование")

            EditPage {

            }
        }

        Tab {
            title: qsTr("Расчёты")

            CalcPage {
                id : calcPage
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
        target: milkCore.db.deliverers
        onError: messageDialog.showError(error)
    }
    Connections {
        target: milkCore.db.localities
        onError: messageDialog.showError(error)
    }
    Connections {
        target: milkCore.db.milkPoints
        onError: messageDialog.showError(error)
    }
    Connections {
        target: milkCore.db.milkReception
        onError: messageDialog.showError(error)
    }

    Connections {
        target: milkCore.db

        onDbOpened: {
            milkCore.settings.main.lastChoosenDb = milkCore.db.dbPath
        }
    }

    Component.onCompleted: {
        milkCore.settings.readSettings();
        if (!milkCore.settings.main.lastChoosenDb.isEmpty)
            milkCore.db.openDb(milkCore.settings.main.lastChoosenDb);
        else {
            fileDialogChooseDb.open()
        }
    }

    Component.onDestruction: {
        milkCore.settings.writeSettings()
    }
}
