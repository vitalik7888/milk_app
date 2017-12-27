import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as C14
import QtQuick.Layouts 1.3
import com.milk.core 1.0
import com.milk.db 1.0

Page {
    DbMilkReception {
        id: curentMilkReception

        model: milkCore.db.milkReception

        deliveryDate: calendarMilkReception.selectedDate
        priceLiter: spinBoxPrice.value
        liters:  spinBoxLiters.value
        fat: spinBoxFat.value

        Component.onCompleted: {
            deliverer.loadData(viewDeliverers.currentMilkId)
            milkPoint.loadData(viewMilkPoints.currentMilkId)
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 4

        ViewLocalities {
            id: viewLocalities

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 160
        }

        ViewDeliverers {
            id: viewDeliverers

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100

            proxy.localityId: viewLocalities.currentMilkId

            onCurrentMilkIdChanged: curentMilkReception.deliverer.loadData(viewDeliverers.currentMilkId)
        }

        ViewMilkPoints {
            id: viewMilkPoints

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100

            proxy.localityId: viewLocalities.currentMilkId

            onCurrentMilkIdChanged: curentMilkReception.milkPoint.loadData(viewMilkPoints.currentMilkId)
        }

        GroupBox {
            id: groupBoxCalcOther

            Layout.alignment: Qt.AlignRight
            Layout.fillHeight: true
            Layout.minimumWidth: 100

            ColumnLayout {
                spacing: 2

                Row {
                    spacing: 6

                    Text {
                        text: qsTr("Цена")
                    }

                    SpinBoxDecimal {
                        id: spinBoxPrice
                        value: milkCore.settings.main.priceLiter
                        onValueChanged: milkCore.settings.main.priceLiter = spinBoxPrice.value
                    }
                }

                Column {
                    spacing: 6

                    Text {
                        text: qsTr("Дата сдачи")
                    }

                    C14.Calendar {
                        id: calendarMilkReception
                    }
                }
                Row {
                    spacing: 6

                    Text {
                        text: qsTr("Литры")
                    }

                    SpinBoxDecimal {
                        id: spinBoxLiters
                        value: 0
                    }


                    Text {
                        text: qsTr("Жир")
                    }

                    SpinBoxDecimal {
                        id: spinBoxFat
                        value: 0
                    }
                }

                Button {
                    id: buttonAddMilkReception
                    text: qsTr("Внести")

                    Layout.alignment: Qt.AlignBottom
                    Layout.fillWidth: true

                    onClicked: {
                        if (spinBoxPrice.value <= 0) {
                            messageDialog.showInfo(qsTr("Укажите цену за литр молока"))
                        } else if (spinBoxLiters.value <= 0) {
                            messageDialog.showInfo(qsTr("Укажите количество литров"))
                        } else if (spinBoxFat.value <= 0) {
                            messageDialog.showInfo(qsTr("Укажите жиры"))
                        } else if (curentMilkReception.deliverer.milkId === -1) {
                            messageDialog.showInfo(qsTr("Выберите сдатчика"))
                        } else if (curentMilkReception.milkPoint.milkId === -1) {
                            messageDialog.showInfo(qsTr("Выберите молокопункт"))
                        } else {
                            if (curentMilkReception.append()) {
                                spinBoxLiters.value = 0.0
                                spinBoxFat.value = 0.0
                            }
                        }
                    }
                }
            }
        }
    }
}
