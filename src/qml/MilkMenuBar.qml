import QtQuick 2.7
import QtQuick.Controls 1.4

MenuBar {
    Menu {
        title: "&File"

        MenuItem {
            action: Action {
                text: qsTr("Open database")
                shortcut: StandardKey.Open
                onTriggered: {
                    fileDialogChooseDb.open()
                }
            }
        }
        MenuItem {
            action: Action {
                text: qsTr("Quit")
                shortcut: StandardKey.Quit
                onTriggered: {
                    Qt.quit()
                }
            }
        }
    }
}
