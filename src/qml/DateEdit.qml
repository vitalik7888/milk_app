import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: dateEdit

    readonly property date currentDate: calendar.selectedDate
    readonly property bool isCalendarOpened: calendar.visible
    property string color: "lightblue"

    signal calendarOpened;
    signal calendarClosed;

    width: textField.width + btnOpen.width
    height: textField.height

    Column {
        id: column
        spacing: 2

        Row {
            spacing: 5
            TextEdit {
                id: textField
                text: calendar.selectedDate
//                readOnly: true

                Keys.onUpPressed: calendar.__selectNextDay()
                Keys.onDownPressed: calendar.__selectPreviousDay()
            }
            Rectangle {
                id: btnOpen
                radius: 5
                width: 30
                height: textField.height
                color: dateEdit.color

                Text {
                    text: "*"
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        dateEdit.isCalendarOpened ?  closeCalendar() : openCalendar()
                    }
                }
            }
        }

        Calendar {
            id: calendar
            visible: false

            onClicked: {
                closeCalendar()
            }

            function open()
            {
                visible = true
            }

            function close()
            {
                visible = false
            }
        }
    }

    function openCalendar()
    {
        calendar.open()
        calendarOpened()
    }

    function closeCalendar()
    {
        calendar.close()
        calendarClosed()
    }
}
