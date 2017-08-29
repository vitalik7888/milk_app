import QtQuick 2.0
import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Milk.Core 1.0
import Milk.Settings 1.0
import Milk.Database 1.0

ApplicationWindow {
    id: window
    visible: true
    property int margin: 11
    width: mainLayout.implicitWidth + 2 * margin
    height: mainLayout.implicitHeight + 2 * margin
    minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
    minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin

    ColumnLayout {
        id: mainLayout
        anchors.margins: margin

        GroupBox {
            Layout.fillWidth: true

            Column {
                spacing: 2

                GroupBox {
                    id: groupBoxFilterDate
                    title: qsTr("Дата")
                    checkable: true
                    checked: false

                    Column {
                        DateEdit {
                            id: dateEditFilterFrom

                            onCalendarOpened: dateEditFilterTo.closeCalendar()
                        }
                        DateEdit {
                            id: dateEditFilterTo

                            onCalendarOpened: dateEditFilterFrom.closeCalendar()
                        }
                    }

                    Component.onCompleted: {
                        onCheckedChanged: {
                            dateEditFilterFrom.closeCalendar()
                            dateEditFilterTo.closeCalendar()
                        }
                    }
                }

                GroupBox {
                    title: qsTr("Выбрать сдатчика")
                    checkable: true
                    checked: false

                    ComboBox {
                    }
                }

                GroupBox {
                    title: qsTr("Выбрать молокопункт")
                    checkable: true
                    checked: false

                    ComboBox {
                    }
                }
            }

            ListView {
                id: listViewCalc
            }
        }
    }

    Connections {
        target: database
        onDbOpened: {

        }
    }

    Component.onCompleted: {
        settings.readSettings()
        if (!settings.main.lastChoosenDb.isEmpty)
            database.openDb(settings.main.lastChoosenDb)
    }
}
