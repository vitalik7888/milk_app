import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4 as C14
import com.milk.core 1.0
import com.milk.db 1.0
import com.milk.calc 1.0

Page {
    id: page

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            Label {
                text: "Filter"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                id: btnMilkMenu
                text: "Filter"
                onClicked: filter.open()
            }
        }
    }

    Filter {
        id: filter

        x: parent.x + parent.width / 2 - width / 2
    }

    C14.TreeView {
        id: viewCalc
        anchors.fill: parent

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

    footer: Row {
        height: 40
        width: parent.width
        spacing: 4

        Button {
            id: buttonCalc
            text: qsTr("Расчёты")

            onClicked: {
                viewCalc.model = milkCore.getCalcItemModel(
                            filter.getDelivererId(), filter.getMilkPointId(),
                            filter.getDateFrom(), filter.getDateTo())
                buttonPrint.enabled = true
            }
        }

        Button {
            id: buttonPrint
            text: qsTr("Печать")
            enabled: false

            onClicked: {
                milkCore.printCalculations(viewCalc.model.calcItemRoot, true)
            }
        }
    }
}
