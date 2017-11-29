import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as C14
import QtQuick.Layouts 1.3
import com.milk.core 1.0
import com.milk.types 1.0
import com.milk.db 1.0

Page {
    MilkReception {
        id: curentMilkReception

        deliveryDate: calendarMilkReception.selectedDate
        priceLiter: spinBoxPrice.value
        liters:  spinBoxLiters.value
        fat: spinBoxFat.value
        deliverer: viewDeliverers.currentMilkItem
        milkPoint: viewMilkPoints.currentMilkItem
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

            filter.locality.localityId: viewLocalities.currentMilkItem.localityId
        }

        ViewMilkPoints {
            id: viewMilkPoints

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 100

            filter.locality.localityId: viewLocalities.currentMilkItem.localityId
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

                    SpinBox {
                        id: spinBoxPrice
                        value: milkCore.settings.main.priceLiter
                        property int decimals: 2

                        textFromValue: function(value, locale) {
                            return Number(value / 100).toLocaleString(locale, 'f', spinBoxPrice.decimals)
                        }

                        valueFromText: function(text, locale) {
                            return Number.fromLocaleString(locale, text) * 100
                        }
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

                    SpinBox {
                        id: spinBoxLiters
                        value: 0
                        property int decimals: 2

                        textFromValue: function(value, locale) {
                            return Number(value / 100).toLocaleString(locale, 'f', spinBoxLiters.decimals)
                        }

                        valueFromText: function(text, locale) {
                            return Number.fromLocaleString(locale, text) * 100
                        }
                    }


                    Text {
                        text: qsTr("Жир")
                    }

                    SpinBox {
                        id: spinBoxFat
                        value: 0
                        property int decimals: 2

                        textFromValue: function(value, locale) {
                            return Number(value / 100).toLocaleString(locale, 'f', spinBoxFat.decimals)
                        }

                        valueFromText: function(text, locale) {
                            return Number.fromLocaleString(locale, text) * 100
                        }
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
                        } else if (viewDeliverers.currentMilkItem === null) {
                            messageDialog.showInfo(qsTr("Выберите сдатчика"))
                        } else if (viewMilkPoints.currentMilkItem === null) {
                            messageDialog.showInfo(qsTr("Выберите молокопункт"))
                        } else if (spinBoxLiters.value <= 0) {
                            messageDialog.showInfo(qsTr("Укажите количество литров"))
                        } else if (spinBoxFat.value <= 0) {
                            messageDialog.showInfo(qsTr("Укажите жиры"))
                        } else {
                            if (milkCore.db.milkReception.append(curentMilkReception)) {
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
