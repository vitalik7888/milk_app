import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import Milk.Types 1.0
import Milk.Database 1.0

Item {
    property Deliverer currentDeliverer
    property alias filter: proxy.deliverer

    GroupBox {
        title: qsTr("Сдатчики")
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent

            TextField {
                id: textFieldFilterName
                placeholderText: qsTr("Фильтр")
                height: 40
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
            }

            ListView {
                id: root

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter

                model: DeliverersSortFilterProxyModel {
                    id: proxy

                    enableDelivererDynamicFilter: true
                    sourceModel: milkCore.db.deliverers
                    deliverer.name: textFieldFilterName.text
                }

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
                    }

                    text: f_name
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

                    onClicked:  {
                        root.forceActiveFocus()
                        root.currentIndex = index
                    }
                }

            }
        }
    }
}
