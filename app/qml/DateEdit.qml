import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as C14
import QtQuick.Layouts 1.3

Rectangle {
    property alias currentDate: calendar.selectedDate

    height: 40
    width: 240

    RowLayout {
        anchors.fill: parent

        Label {
            text: qsTr("Д:")
        }

        TextField {
            id: textFieldDay
            Layout.preferredWidth: 40
            text: calendar.selectedDate.getDate()
            readOnly: true
            Keys.onUpPressed: calendar.__selectNextDay()
            Keys.onDownPressed: calendar.__selectPreviousDay()
//            Keys.onRightPressed: to month
        }
        Label {
            text: qsTr("М:")
        }

        TextField {
            id: textFieldMonth
            Layout.preferredWidth: 40
            text: calendar.selectedDate.getMonth()
            readOnly: true
            Keys.onUpPressed: calendar.__selectNextMonth()
            Keys.onDownPressed: calendar.__selectPreviousMonth()
        }
        Label {
            text: qsTr("Г:")
        }

        TextField {
            id: textFieldYear
            Layout.preferredWidth: 60
            text: calendar.selectedDate.getFullYear()
            readOnly: true
            Keys.onUpPressed: calendar.selectNextYear()
            Keys.onDownPressed: calendar.selectPreviousYear()
        }

        ToolButton {
            id: btnOpenCalendar
            text: ":"
            width: 20
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft

            onClicked: {
                popup.open()
            }

        }
    }

    Popup {
        id: popup
        width: 250
        height: 250
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        C14.Calendar {
            id: calendar
            anchors.fill: parent

            function selectNextYear() {
                selectedDate = new Date(selectedDate.getFullYear() + 1,
                                        selectedDate.getMonth(),
                                        selectedDate.getDate())
            }

            function selectPreviousYear() {
                selectedDate = new Date(selectedDate.getFullYear() - 1,
                                        selectedDate.getMonth(),
                                        selectedDate.getDate())
            }
        }
    }
}
