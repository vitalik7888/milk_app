import QtQuick 2.7

Item {
    Shortcut {
        sequence: StandardKey.Open
        onActivated: fileDialogChooseDb.open()
    }

    Shortcut {
        sequence: StandardKey.New
        onActivated: dialogs.dialogAddEditLocality.openInsert()
    }

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }
}
