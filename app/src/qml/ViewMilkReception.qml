import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as C14
import com.milk.core 1.0
import com.milk.types 1.0
import com.milk.db 1.0

Item {
    readonly property alias milkTable: proxy.sourceModel
    readonly property alias proxy: proxy
    readonly property alias viewTable: viewTable
    property MilkReception currentMilkItem

    function currentSourceRow() {
        return proxy.sourceRow(viewTable.currentIndex)
    }

    height: 200
    width: 160

    Filter {
        id: filter

        onClosed: {
            proxy.delivererId = getDelivererId()
            proxy.milkPointId = getMilkPointId()
            proxy.minDate = getDateFrom() == null ? "" : getDateFrom()
            proxy.maxDate = getDateTo() == null ? "" : getDateTo()
        }
    }

    Dialog {
        id: dialogChooseDeliverer
        title: qsTr("Выбор сдатчика")
        width: 300
        height: 400
        standardButtons: Dialog.Ok | Dialog.Cancel
        property int delivererRow: -1

        ColumnLayout {
            anchors.fill: parent
            spacing: 2

            ViewDeliverers {
                id: _viewDeliverers
                viewMenu.visible: false
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Label {
                id: _errorDelivererLabel
                color: "red"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignBottom
            }
        }

        onAccepted: {
            if (!check()) {
                open()
                return
            }
            if (milkTable.setValue(delivererRow, DBC.TMR_ID_DELIVERER, _viewDeliverers.currentMilkItem.delivererId)) {
                console.log("Deliverer in milk reception changed")
            }
        }
        onClosed: {
            milkPointRow = -1
            _errorDelivererLabel.text = ""
        }

        function check() {
            if (_viewDeliverers.currentMilkItem == null)
            {
                _errorDelivererLabel.text = qsTr("Выберите сдатчика")
                return false
            }
            if (delivererRow <= 0) {
                console.log(qsTr("Передана неверная строка"))
                return false
            }

            return true
        }
    }

    Dialog {
        id: dialogChooseMilkPoint
        title: qsTr("Выбор молокопункта")
        width: 300
        height: 400
        standardButtons: Dialog.Ok | Dialog.Cancel
        property int milkPointRow: -1

        onAccepted: {
            if (!check()) {
                open()
                return
            }
            if (milkTable.setValue(milkPointRow, DBC.TMR_MILK_POINT_ID, _viewMilkPoints.currentMilkItem.milkPointId)) {
                console.log("MilkPoint in milk reception changed")
            }
        }
        onClosed: {
            milkPointRow = -1
            _errorMilkPointsLabel.text = ""
        }

        function check() {
            if (_viewMilkPoints.currentMilkItem == null)
            {
                _errorMilkPointsLabel.text = qsTr("Выберите молокопункт")
                return false
            }
            if (milkPointRow <= 0) {
                console.log(qsTr("Передана неверная строка"))
                return false
            }

            return true
        }

        GridLayout {
            anchors.fill: parent
            columns: 2
            rows: 2

            ViewLocalities {
                id: _viewLocalities
                viewMenu.visible: false
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ViewMilkPoints{
                id: _viewMilkPoints
                viewMenu.visible: false
                Layout.fillWidth: true
                Layout.fillHeight: true
                filter.locality.localityId : _viewLocalities.filter.localityId
            }

            Label {
                id: _errorMilkPointsLabel
                color: "red"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignBottom
                Layout.columnSpan: 2
            }
        }
    }

    Dialog {
        id: dialogChooseDate
        title: qsTr("Выбор даты")
        width: 400
        height: 400
        standardButtons: Dialog.Ok | Dialog.Cancel
        property int milkItemRow: -1

        C14.Calendar {
            id: _calendar
            anchors.fill: parent
        }

        onAccepted: {
            if (milkTable.setValue(milkItemRow, DBC.TMR_DELIVERY_DATE, _calendar.selectedDate)) {
                console.log("Delivery date in milk reception has been changed")
            }
        }

        onOpened: _calendar.selectedDate = milkTable.getValue(milkItemRow, DBC.TMR_DELIVERY_DATE)
    }

    Dialog {
        id: dialogChangeDouble
        standardButtons: Dialog.Ok | Dialog.Cancel
        property int row: -1
        property int column: -1

        SpinBoxDecimal {
            id: _spinBoxDecimal
            width: 100
            height: 60
            anchors.fill: parent
        }

        onAccepted: {
            if (milkTable.setValue(row, column, _spinBoxDecimal.value))
                console.log("Double value in milk reception has been changed")
        }

        onOpened: _spinBoxDecimal.value = milkTable.getValue(row, column)
    }

    Dialog {
        id: dialogRemoveMilkReception

        title: qsTr("Удаление приёма молока")
        modal: true
        standardButtons: Dialog.Ok

        property int row: -1

        Label{
            id: _content
        }

        onAccepted: {
            if (row == -1) {
                close()
                return
            }

            if (milkTable.remove(row)) {
                console.log(qsTr("Приём молока успешно удалён"))
            }
            row = -1
        }

        onOpened: {
            var _item = milkTable.get(row)
            if (_item == null)
                _content.text = qsTr("Выберите приём молока")
            else
                _content.text = "Вы действительно желаете удалить '" + _item.deliverer.name + ": "
                        + _item.deliveryDate.toLocaleDateString() + "'?\n"
        }

    }

    GroupBox {
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            spacing: 4

            ToolBar {
                id: viewMenu
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop

                RowLayout {
                    ToolButton {
                        text: "Filter"

                        onClicked: {
                            filter.open()
                        }
                    }
                }
            }

            ListView {
                id: viewTable

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                Layout.minimumWidth: 100

                model: MilkReceptionSortFilterProxyModel {
                    id: proxy
                    sourceModel: milkCore.db.milkReception
                }

                onCurrentIndexChanged: {
                    currentMilkItem = currentItem == null ? null : milkTable.get(currentIndex)
                }

                remove: Transition {
                    ParallelAnimation {
                        NumberAnimation { property: "opacity"; to: 0; duration: 1000 }
                        NumberAnimation { properties: "x,y"; to: 100; duration: 1000 }
                    }
                }

                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                delegate: ItemDelegate {
                    width: parent.width

                    onClicked:  {
                        viewTable.forceActiveFocus()
                        viewTable.currentIndex = index
                    }

                    RowLayout {
                        spacing: 4

                        Label {
                            text: f_id
                        }
                        ToolButton {
                            text: f_deliv_first_name + ' ' + f_deliv_last_name
                            onClicked: {
                                dialogChooseDeliverer.delivererRow = proxy.sourceRow(index)
                                dialogChooseDeliverer.open()
                            }
                        }
                        ToolButton {
                            text: f_milk_point_name
                            onClicked: {
                                dialogChooseMilkPoint.milkPointRow = proxy.sourceRow(index)
                                dialogChooseMilkPoint.open()
                            }
                        }
                        ToolButton {
                            text: f_delivery_date
                            onClicked: {
                                dialogChooseDate.milkItemRow = proxy.sourceRow(index)
                                dialogChooseDate.open()
                            }
                        }
                        ToolButton {
                            text: f_price_liter

                            onClicked: {
                                dialogChangeDouble.title = qsTr("Изменение цены")
                                dialogChangeDouble.row = proxy.sourceRow(index)
                                dialogChangeDouble.column = DBC.TMR_PRICE_LITER
                                dialogChangeDouble.open()
                            }
                        }
                        ToolButton {
                            text: f_liters

                            onClicked: {
                                dialogChangeDouble.title = qsTr("Изменение литража")
                                dialogChangeDouble.row = proxy.sourceRow(index)
                                dialogChangeDouble.column = DBC.TMR_LITERS
                                dialogChangeDouble.open()
                            }
                        }
                        ToolButton {
                            text: f_fat

                            onClicked: {
                                dialogChangeDouble.title = qsTr("Изменение жирности")
                                dialogChangeDouble.row = proxy.sourceRow(index)
                                dialogChangeDouble.column = DBC.TMR_FAT
                                dialogChangeDouble.open()
                            }
                        }

                        ToolButton {
                            width: 32
                            height: 32

                            Image {
                                source: "/img/remove"
                                anchors.fill: parent
                            }
                            onClicked: {
                                dialogRemoveMilkReception.row = proxy.sourceRow(index)
                                dialogRemoveMilkReception.open()
                            }
                        }
                    }
                }

            }
        }
    }

    Connections {
        target: milkCore.db
        onMilkReceptionChanged: viewTable.currentIndex = 0
    }
}
