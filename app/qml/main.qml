import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2
import com.milk.core 1.0
import com.milk.settings 1.0
import com.milk.db 1.0
import com.milk.plugins 1.0

ApplicationWindow {
    id: appWindow
    title: qsTr("Milk app")
    visible: true

    width: 900
    height: 600
    minimumWidth: 800
    minimumHeight: 480

    Dialogs {
        id: dialogs
        anchors.centerIn: parent
    }

    menuBar: MilkMenu { }

    ViewDbExporter {
        id: viewDbExporter
    }

    ViewSettings {
        id: viewSettings
        x: parent.x + width / 2
    }

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

    SwipeView {
        id: mainView
        currentIndex: bar.currentIndex
        anchors.fill: parent

        MilkReceptionsPage {
            id: milkReceptionPage
        }

        CalcPage {
            id: calcPage
        }

        Page {
            ViewMilkReception {
                anchors.fill: parent
            }
        }
    }

    footer:  TabBar {
        id: bar
        width: parent.width
        currentIndex: 0

        TabButton {
            text: qsTr("Сдача молока")
        }
        TabButton {
            text: qsTr("Расчёты")
        }
        TabButton {
            text: qsTr("Редакт. сдач молока")
        }
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
//        milkCore.settings.writeSettings()
    }
}
