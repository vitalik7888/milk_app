import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import Milk.Types 1.0
import Milk.Database 1.0

Item {
    property MilkPoint currentMilkPoint
    property alias filter: proxy.milkPoint

    GroupBox {
        title: qsTr("Молокопункт")
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
                id: view
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter

                model: MilkPointsSortFilterProxyModel {
                    id: proxy
                    sourceModel: milkCore.db.milkPoints
                    enableMilkPointDynamicFilter: true
                    milkPoint.name: textFieldFilterName.text
                }

                onCurrentItemChanged: {
                    currentMilkPoint = currentItem.milkPoint
                }

                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                delegate: ItemDelegate {
                    property MilkPoint milkPoint: MilkPoint {
                        milkPointId: f_id
                        name: f_name
                        description: f_description
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
                        view.forceActiveFocus()
                        view.currentIndex = index
                    }
                }
            }
        }
    }
}
