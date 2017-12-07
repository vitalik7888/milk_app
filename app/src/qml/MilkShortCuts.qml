import QtQuick 2.9

Item {
    Shortcut {
        sequence: StandardKey.Open
        onActivated: fileDialogChooseDb.open()
    }

    Shortcut {
        sequence: "ctrl+shift+P"
        onActivated: viewSettings.open()
    }

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }
}
