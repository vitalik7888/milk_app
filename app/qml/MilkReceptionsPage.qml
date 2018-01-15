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
        }

        ViewMilkPoints {
            id: viewMilkPoints

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100

            proxy.localityId: viewLocalities.currentMilkId
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
                        value: 0.0
                    }


                    Text {
                        text: qsTr("Жир")
                    }

                    SpinBoxDecimal {
                        id: spinBoxFat
                        value: 0.0
                    }
                }

                Button {
                    id: buttonAddMilkReception
                    text: qsTr("Внести")

                    Layout.alignment: Qt.AlignBottom
                    Layout.fillWidth: true

                    onClicked: {
                        if (spinBoxPrice.value <= 0) {
                            dialogs.messageDialog.showInfo(qsTr("Укажите цену за литр молока"))
                        } else if (spinBoxLiters.value <= 0) {
                            dialogs.messageDialog.showInfo(qsTr("Укажите количество литров"))
                        } else if (calendarMilkReception.selectedDate === null) {
                            dialogs.messageDialog.showInfo(qsTr("Выберите дату"))
                        } else if (spinBoxFat.value <= 0) {
                            dialogs.messageDialog.showInfo(qsTr("Укажите жиры"))
                        } else if (viewDeliverers.currentMilkId <= 0) {
                            dialogs.messageDialog.showInfo(qsTr("Выберите сдатчика"))
                        } else if (viewMilkPoints.currentMilkId <= 0) {
                            dialogs.messageDialog.showInfo(qsTr("Выберите молокопункт"))
                        } else {
                            curentMilkReception.deliverer.loadData(viewDeliverers.currentMilkId)
                            curentMilkReception.milkPoint.loadData(viewMilkPoints.currentMilkId)
                            curentMilkReception.deliveryDate = calendarMilkReception.selectedDate
                            curentMilkReception.priceLiter = milkCore.settings.main.priceLiter
                            curentMilkReception.liters =  spinBoxLiters.value
                            curentMilkReception.fat = spinBoxFat.value

                            if (curentMilkReception.append()) {
                                console.log("MilkReception was added")
                                spinBoxLiters.value = 0.0
                                spinBoxFat.value = 0.0
                                curentMilkReception.reset()
                            }
                        }
                    }
                }
            }
        }
    }
}
