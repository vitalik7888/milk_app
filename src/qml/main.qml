import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import MilkCore 1.0
import Database 1.0

ApplicationWindow {
    id: window
    width: 480
    height: 600
    visible: true

    Component.onCompleted: {
        if (!core.settings.main.lastChoosenDb.isEmpty)
            core.database.openDb(core.settings.main.lastChoosenDb)
    }

    Connections {
        target: core.database
        onDbOpened: {
            console.log("Database is opened")
        }
    }
}
