import QtQuick 2.9
import Qt.labs.platform 1.0 as Labs10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.milk.core 1.0
import com.milk.types 1.0
import com.milk.settings 1.0
import com.milk.db 1.0

ApplicationWindow {
    id: appWindow
    title: qsTr("Milk app")
    visible: true

    width: 800
    height: 600
    minimumWidth: 640
    minimumHeight: 480

    MilkCore {
        id: milkCore
    }

    MilkMenu {
        id: milkMenu

        x: btnMilkMenu.x
        y: btnMilkMenu.y
    }

    MilkShortCuts {}

    Dialogs {
        id: dialogs
    }

    Labs10.MessageDialog {
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

    Labs10.FileDialog {
        id: fileDialogChooseDb

        title: qsTr("Выберите или создайте базу данных")
        //        selectMultiple: false

        onAccepted: {
            milkCore.db.openDb(currentFile.toString().replace("file://", ""))
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                text: ""
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                id: btnMilkMenu
                text: qsTr("⋮")
                onClicked: milkMenu.open()
            }

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
    }

    footer:  TabBar {
        id: bar
        width: parent.width
        currentIndex: 1

        TabButton {
            text: qsTr("Сдача молока")
        }
        TabButton {
            text: qsTr("Расчёты")
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
        milkCore.settings.writeSettings()
    }
}
