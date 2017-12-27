import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import com.milk.core 1.0
import com.milk.db 1.0

Popup {
    id: popup
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    function getDelivererId() {
        return checkBoxFilterDeliverer.checked ? viewDeliverers.currentMilkId : -1
    }

    function getMilkPointId() {
        return checkBoxFilterMilkPoint.checked ? viewMilkPoints.currentMilkId : -1
    }

    function getDateFrom() {
        return checkBoxFilterDate.checked ? dateEditFrom.currentDate : null
    }

    function getDateTo() {
        return checkBoxFilterDate.checked ? dateEditTo.currentDate : null
    }
    height: 500

    GridLayout {
        anchors.fill: parent
        columns: 3
        rows: 2

        GroupBox {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            height: 40
            title: qsTr("Дата")

            label: CheckBox {
                id: checkBoxFilterDate
                checked: false
                text: qsTr("Выбрать даты")
            }

            ColumnLayout {
                Layout.fillWidth: true
                enabled: checkBoxFilterDate.checked

                DateEdit {
                    id: dateEditFrom
                    Layout.fillWidth: true
                }

                DateEdit {
                    id: dateEditTo
                    Layout.fillWidth: true
                }
            }
        }

        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.rowSpan: 2

            label: CheckBox {
                id: checkBoxFilterMilkPoint
                checked: false
                text: qsTr("Выбрать молокопункт")
            }
            ViewMilkPoints {
                id: viewMilkPoints
                anchors.fill: parent
                enabled: checkBoxFilterMilkPoint.checked

                proxy.localityId: viewLocalities.currentMilkId
            }
        }

        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.rowSpan: 2

            label: CheckBox {
                id: checkBoxFilterDeliverer
                checked: false
                text: qsTr("Выбрать сдатчика")
            }
            ViewDeliverers {
                id: viewDeliverers
                anchors.fill: parent
                enabled: checkBoxFilterDeliverer.checked

                proxy.localityId: viewLocalities.currentMilkId
            }
        }

        ViewLocalities {
            Layout.fillWidth: true
            Layout.fillHeight: true

            id: viewLocalities
        }
    }
}
