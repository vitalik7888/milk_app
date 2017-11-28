import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as C14

Popup {
    id: popup
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    function getDelivererId() {
        return checkBoxFilterDeliverer.checked ? viewDeliverers.currentDeliverer.delivererId : -1
    }

    function getMilkPointId() {
        return checkBoxFilterMilkPoint.checked ? viewMilkPoints.currentMilkPoint.milkPointId : -1
    }

    function getDateFrom() {
        return checkBoxFilterDate.checked ? calendarFrom.selectedDate : null
    }

    function getDateTo() {
        return checkBoxFilterDate.checked ? calendarTo.selectedDate : null
    }

    RowLayout {
        anchors.fill: parent

        GroupBox {
            label: CheckBox {
                id: checkBoxFilterDate
                checked: false
                text: qsTr("Выбрать даты")
            }

            title: qsTr("Дата")

            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft

            ColumnLayout {
                Layout.fillHeight: true

                enabled: checkBoxFilterDate.checked

                Text {
                    text: qsTr("С")
                }

                C14.Calendar {
                    id: calendarFrom
                }

                Text {
                    text: qsTr("По")
                }

                C14.Calendar {
                    id: calendarTo
                }
            }
        }

        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100

            ViewLocalities {
                id: viewLocalities

                anchors.fill: parent
            }
        }

        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100

            label: CheckBox {
                id: checkBoxFilterMilkPoint
                checked: false
                text: qsTr("Выбрать молокопункт")
            }
            ViewMilkPoints {
                id: viewMilkPoints
                anchors.fill: parent
                enabled: checkBoxFilterMilkPoint.checked

                filter.locality.localityId: viewLocalities.currentLocality.localityId
            }
        }

        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100

            label: CheckBox {
                id: checkBoxFilterDeliverer
                checked: false
                text: qsTr("Выбрать сдатчика")
            }
            ViewDeliverers {
                id: viewDeliverers
                anchors.fill: parent
                enabled: checkBoxFilterDeliverer.checked

                filter.locality.localityId: viewLocalities.currentLocality.localityId
            }
        }
    }
}
