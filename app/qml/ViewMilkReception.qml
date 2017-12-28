import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as C14
import com.milk.core 1.0
import com.milk.db 1.0

Item {
    height: 200
    width: 160

    readonly property alias milkTable: proxy.sourceModel
    readonly property alias proxy: proxy
    readonly property alias viewModel: viewModel
    readonly property alias viewMenu: viewMenu
    readonly property DbMilkReception currentMilkItem: DbMilkReception {
        model: milkCore.db.milkReception
    }

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

        onOpened: {
            _viewDeliverers.proxy.resetFilter()
            _viewDeliverers.viewModel.currentIndex = currentMilkItem.deliverer.getPositionInModel()
        }

        onAccepted: {
            if (!check()) {
                open()
                return
            }

            currentMilkItem.deliverer.loadData(_viewDeliverers.currentMilkId)
            if (currentMilkItem.saveDelivererId()) {
                console.log("Deliverer in milk reception changed")
            }
        }

        function check() {
            if (_viewDeliverers.currentMilkId === -1)
            {
                _errorDelivererLabel.text = qsTr("Выберите сдатчика")
                return false
            }

            _errorDelivererLabel.text = ""
            return true
        }
    }

    Dialog {
        id: dialogChooseMilkPoint
        title: qsTr("Выбор молокопункта")
        width: 300
        height: 400
        standardButtons: Dialog.Ok | Dialog.Cancel

        onOpened: {
            _viewMilkPoints.proxy.resetFilter()
            _viewLocalities.viewModel.currentIndex = currentMilkItem.milkPoint.locality.getPositionInModel()
            _viewMilkPoints.viewModel.currentIndex = currentMilkItem.milkPoint.getPositionInModel()
        }

        onAccepted: {
            if (!check()) {
                open()
                return
            }
            currentMilkItem.milkPoint.loadData(_viewMilkPoints.currentMilkId)
            if (currentMilkItem.saveMilkPointId()) {
                console.log("MilkPoint in milk reception changed")
            }

            _errorMilkPointsLabel.text = ""
        }

        function check() {
            if (_viewMilkPoints.currentMilkId === -1)
            {
                _errorMilkPointsLabel.text = qsTr("Выберите молокопункт")
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
                proxy.localityId : _viewLocalities.currentMilkId
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

        C14.Calendar {
            id: _calendar
            anchors.fill: parent
        }

        onAccepted: {
            currentMilkItem.setDeliveryDate(_calendar.selectedDate)
            if (currentMilkItem.saveDeliveryDate()) {
                console.log("Delivery date in milk reception has been changed")
            }
        }

        onOpened: _calendar.selectedDate = currentMilkItem.deliveryDate
    }

    Dialog {
        id: dialogChangeDouble
        standardButtons: Dialog.Ok | Dialog.Cancel
        property int role: -1
        property alias value: _spinBoxDecimal.value

        ColumnLayout {
            anchors.fill: parent

            SpinBoxDecimal {
                id: _spinBoxDecimal
                Layout.alignment: Qt.AlignTop
                anchors.centerIn: parent
            }
            Label {
                id: _errors
                Layout.alignment: Qt.AlignBottom
                color: "red"
            }
        }

        onAccepted: {
            if (!check()) {
                open()
                return
            }

            if (currentMilkItem.saveValue(value, role))
                console.log("Double value in milk reception has been changed")

            role = -1
            _spinBoxDecimal.value = 0.0
            _errors.text = ""
        }

        function check() {
            if (role < 0) {
                console.log(qsTr("Role is invalid"))
                return false
            }
            if (value <= 0.0) {
                _errors.text = qsTr("Значение должно быть > 0")
                return false
            }

            return true;
        }
    }

    Dialog {
        id: dialogRemoveMilkReception

        title: qsTr("Удаление приёма молока")
        modal: true
        standardButtons: Dialog.Ok

        Label{
            id: _content
        }

        onAccepted: {
            if (currentMilkItem.milkId === -1) {
                close()
                return
            }

            if (currentMilkItem.remove()) {
                console.log(qsTr("Приём молока успешно удалён"))
            }
        }

        onOpened: {
            if (currentMilkItem.milkId === -1)
                _content.text = qsTr("Выберите приём молока")
            else
                _content.text = "Вы действительно желаете удалить '" +
                        currentMilkItem.deliveryDate.toLocaleDateString() + "'?\n"
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
                id: viewModel

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                Layout.minimumWidth: 100

                model: MilkReceptionSortFilterProxyModel {
                    id: proxy
                    sourceModel: milkCore.db.milkReception
                }

                onCurrentIndexChanged: {
                    if (currentItem != null)
                        currentMilkItem.loadData(currentItem._milkId)
                    else
                        currentMilkItem.reset()
                }

                remove: Transition {
                    ParallelAnimation {
                        NumberAnimation { property: "opacity"; to: 0; duration: 1000 }
                        NumberAnimation { properties: "x,y"; to: 100; duration: 1000 }
                    }
                }

                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                delegate: ItemDelegate {
                    property int _milkId: model.milkId
                    width: parent.width

                    onClicked:  {
                        viewModel.forceActiveFocus()
                        viewModel.currentIndex = index
                    }

                    RowLayout {
                        spacing: 4

                        Label {
                            text: model.milkId
                        }

                        ToolButton {
                            text: model.delivererFullName
                            onClicked: {
                                dialogChooseDeliverer.open()
                            }
                        }
                        ToolButton {
                            text: model.milkPointName
                            onClicked: {
                                dialogChooseMilkPoint.open()
                            }
                        }
                        ToolButton {
                            text: deliveryDate
                            onClicked: {
                                dialogChooseDate.open()
                            }
                        }
                        ToolButton {
                            text: priceLiter

                            onClicked: {
                                dialogChangeDouble.title = qsTr("Изменение цены")
                                dialogChangeDouble.value = currentMilkItem.priceLiter
                                dialogChangeDouble.role = DBC.MR_PriceLiterRole
                                dialogChangeDouble.open()
                            }
                        }
                        ToolButton {
                            text: liters

                            onClicked: {
                                dialogChangeDouble.title = qsTr("Изменение литража")
                                dialogChangeDouble.value = currentMilkItem.liters
                                dialogChangeDouble.role = DBC.MR_LitersRole
                                dialogChangeDouble.open()
                            }
                        }
                        ToolButton {
                            text: fat

                            onClicked: {
                                dialogChangeDouble.title = qsTr("Изменение жирности")
                                dialogChangeDouble.value = currentMilkItem.fat
                                dialogChangeDouble.role = DBC.MR_FatRole
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
                                viewModel.currentIndex = index
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
        onMilkReceptionChanged: viewModel.currentIndex = 0
    }
}
