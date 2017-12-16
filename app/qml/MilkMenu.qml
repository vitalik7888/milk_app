import QtQuick 2.9
import QtQuick.Controls 2.3

MenuBar {
    Menu {
        title: "Main"

        Action {
            text: qsTr("Открыть базу данных")
            shortcut: StandardKey.Open
            onTriggered: fileDialogChooseDb.open()
        }

        Action {
            text: qsTr("Экспорт бд")
            onTriggered: viewDbExporter.open()
        }

        MenuSeparator {}

        Action {
            text: qsTr("Настройки")
            shortcut: "ctrl+shift+P"
            onTriggered: viewSettings.open()
        }

        Action {
            text: qsTr("Выход")
            shortcut: StandardKey.Quit
            onTriggered: Qt.quit()
        }
    }
}
