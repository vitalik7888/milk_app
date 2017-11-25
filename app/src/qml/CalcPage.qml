import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as C14
import MilkCore 1.0
import Milk.Database 1.0
import Milk.Calc 1.0

Page {

    Item {
        id: filter

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
    }

    SwipeView {
        id: view

        currentIndex: 1
        anchors.fill: parent

        Item {
            id: filterPage

            GroupBox {
                title: qsTr("Фильтр")

                anchors.fill: parent

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

                        Column {
                            anchors.fill: parent

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
        }

        Item {
            id: calcViewPage

            ColumnLayout {
                anchors.fill: parent

                C14.TreeView {
                    id: viewCalc

                    Layout.alignment: Qt.AlignCenter
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    C14.TableViewColumn {
                        title: "Name"
                        role: "name"
                        width: 150
                    }
                    C14.TableViewColumn {
                        title: "Date"
                        role: "date"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "MilkPointName"
                        role: "mpName"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "Price"
                        role: "price"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "Liters"
                        role: "liters"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "Fat"
                        role: "fat"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "Protein"
                        role: "protein"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "FatUnits"
                        role: "fatUnits"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "RankWeight"
                        role: "rankWeight"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "Payment"
                        role: "payment"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "Premium"
                        role: "premium"
                        width: 80
                    }
                    C14.TableViewColumn {
                        title: "Sum"
                        role: "sum"
                        width: 80
                    }

                    itemDelegate: Item {
                        Text {
                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            color: styleData.textColor
                            elide: styleData.elideMode
                            text: styleData.value
                        }
                    }
                }

                Button {
                    id: buttonCalc
                    Layout.alignment: Qt.AlignBottom

                    text: qsTr("Расчёты")

                    onClicked: {
                        viewCalc.model = milkCore.getCalcItemModel(
                                    filter.getDelivererId(), filter.getMilkPointId(),
                                    filter.getDateFrom(), filter.getDateTo())
                    }
                }
            }
        }
    }

    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
