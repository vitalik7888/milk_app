import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Milk.Core 1.0
import Milk.Database 1.0

Page {
    MilkReception {
        id: curentMilkReception

        deliveryDate: calendarMilkReception.selectedDate
        priceLiter: spinBoxPrice.value
        liters:  spinBoxLiters.value
        fat: spinBoxFat.value
        deliverer: listViewCalcDeliverers.currentDeliverer
        milkPoint: listViewCalcMilkPoints.currentMilkPoint
    }

    LocalitiesSortFilterProxyModel {
        id: localitiesProxy

        sourceModel: milkDb.localities
        enableLocalityDynamicFilter: true
    }

    MilkPointsSortFilterProxyModel {
        id: milkPointsProxy

        enableMilkPointDynamicFilter: true
        sourceModel: milkDb.milkPoints
        milkPoint.locality.localityId: listViewCalcLocalities.currentLocality.localityId
    }

    DeliverersSortFilterProxyModel {
        id: deliverersProxy

        enableDelivererDynamicFilter: true
        sourceModel: milkDb.deliverers
        deliverer.locality.localityId: listViewCalcLocalities.currentLocality.localityId
    }

    RowLayout {
        anchors.fill: parent
        spacing: 4

        ListViewLocalities {
            id: listViewCalcLocalities

            Layout.fillHeight: true
            Layout.minimumWidth: 100

            model: localitiesProxy
        }

        ListViewDeliverers {
            id: listViewCalcDeliverers

            Layout.fillHeight: true
            Layout.minimumWidth: 100

            model: deliverersProxy
        }

        ListViewMilkPoints {
            id: listViewCalcMilkPoints

            Layout.fillHeight: true
            Layout.minimumWidth: 100

            model: milkPointsProxy
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

                        decimals: 2
                        value: milkSettings.main.priceLiter
                    }
                }

                Column {
                    spacing: 6

                    Text {
                        text: qsTr("Дата сдачи")
                    }

                    Calendar {
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

                        decimals: 2
                        value: 0.0
                    }


                    Text {
                        text: qsTr("Жир")
                    }

                    SpinBox {
                        id: spinBoxFat

                        decimals: 2
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
                            messageDialog.showInfo(qsTr("Укажите цену за литр молока"))
                        } else if (listViewCalcDeliverers.currentDeliverer === null) {
                            messageDialog.showInfo(qsTr("Выберите сдатчика"))
                        } else if (listViewCalcMilkPoints.currentMilkPoint === null) {
                            messageDialog.open(qsTr("Выберите молокопункт"))
                        } else if (spinBoxLiters.value <= 0) {
                            messageDialog.open(qsTr("Укажите количество литров"))
                        } else if (spinBoxFat.value <= 0) {
                            messageDialog.open(qsTr("Укажите жиры"))
                        } else {
                            if (milkDb.milkReception.append(curentMilkReception)) {
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
