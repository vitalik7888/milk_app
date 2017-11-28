import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import MilkCore 1.0
import Milk.Types 1.0
import Milk.Database 1.0

Item {
//    id: root

    property Deliverer currentDeliverer
    property alias filter: proxy.deliverer

    function removeCurrentRow() {
        return removeRow(view.currentIndex)
    }

    function removeRow(row) {
        return milkCore.db.deliverers.removeRowByIndex(proxy.sourceIdIndex(row))
    }

    GroupBox {
        title: qsTr("Сдатчики")
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            spacing: 4

            TextField {
                id: textFieldFilterName
                placeholderText: qsTr("Фильтр")
                height: 40
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
            }

            ListView {
                id: view

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter

                model: DeliverersSortFilterProxyModel {
                    id: proxy

                    enableDelivererDynamicFilter: true
                    sourceModel: milkCore.db.deliverers
                    deliverer.name: textFieldFilterName.text
                }
                currentIndex: 0

                onCurrentItemChanged: {
                    currentDeliverer = currentItem.deliverer
                }

                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                delegate: ItemDelegate {
                    property Deliverer deliverer: Deliverer {
                        delivererId: f_id
                        name: f_name
                        inn: f_inn
                        address: f_address
                        phoneNumber: f_phone_number

                        function remove() {
                            removeRow(index)
                        }
                    }

                    text: deliverer.name
                    width: parent.width

                    contentItem: Text {
                        text: parent.text
                        font: parent.font
                        color: parent.enabled ? parent.Material.primaryTextColor
                                              : parent.Material.hintTextColor
                        elide: Text.ElideRight
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    ToolButton {
                        id: btnDeliverersMenu
                        text: qsTr("⋮")
                        width: 10

                        height: parent.height
                        x: parent.x + parent.width - width

                        onClicked: {
                            var pos = btnDeliverersMenu.mapToItem(itemDeliverers, 0, 0)
                            itemDeliverers.menu.x = pos.x - itemDeliverers.menu.width / 2
                            itemDeliverers.menu.y = pos.y
                            itemDeliverers.menu.deliverer = deliverer
                            itemDeliverers.menu.open()
                        }

                    }

                    onClicked:  {
                        view.forceActiveFocus()
                        view.currentIndex = index
                    }
                }

            }
        }
    }
}
