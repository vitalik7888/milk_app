import QtQuick 2.9
import QtQuick.Controls 2.2

Menu {
    title: "&File"

    MenuItem {
        text: qsTr("Открыть базу данных")
        onTriggered: fileDialogChooseDb.open()
    }

    MenuItem {
        text: qsTr("Настройки")
        onTriggered: viewSettings.open()
    }

    MenuItem {
        text: qsTr("Quit")
        onTriggered: Qt.quit()
    }
}
