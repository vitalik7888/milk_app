import QtQuick 2.9
import QtQuick.Controls 2.2

Menu {
    title: "&File"

    MenuItem {
        text: qsTr("Открыть базу данных")
        onTriggered: fileDialogChooseDb.open()
    }

    MenuItem {
        text: qsTr("Добавить населенный пункт")
        onTriggered: itemLocalities.dialogAddEditLocality.openInsert()
    }

    MenuItem {
        text: qsTr("Quit")
        onTriggered: Qt.quit()
    }
}
