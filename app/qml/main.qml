import QtQuick 2.9
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
        target: milkCore.db
        onDbOpened: {
            milkCore.settings.main.lastChoosenDb = milkCore.db.dbPath
        }
    }
    Connections {
        target: milkCore.db.deliverers.dao
        onSqlError: dialogs.dbErrorsDialog.text = errorDescription
    }
    Connections {
        target: milkCore.db.localities.dao
        onSqlError: dialogs.dbErrorsDialog.text = errorDescription
    }
    Connections {
        target: milkCore.db.milkPoints.dao
        onSqlError: dialogs.dbErrorsDialog.text = errorDescription
    }
    Connections {
        target: milkCore.db.milkReception.dao
        onSqlError: dialogs.dbErrorsDialog.text = errorDescription
    }

    Component.onCompleted: {
        milkCore.settings.readSettings();
        if (milkCore.settings.main.lastChoosenDb) {
            milkCore.db.openDb(milkCore.settings.main.lastChoosenDb);
        } else {
            dialogs.messageDialog.showInfo(qsTr("Создайте или выберите базу данных для дальнейшей работы"))
        }
    }

    Component.onDestruction: {
        milkCore.settings.writeSettings()
    }
}
