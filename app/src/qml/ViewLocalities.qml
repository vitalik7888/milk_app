import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import Milk.Types 1.0
import Milk.Database 1.0

Item {
    property Locality currentLocality
    property alias filter: proxy.locality

    GroupBox {
        title: qsTr("Населенный пункт")
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

                model: LocalitiesSortFilterProxyModel {
                    id: proxy

                    sourceModel: milkCore.db.localities
                    enableLocalityDynamicFilter: true
                    locality.name: textFieldFilterName.text
                }

                onCurrentItemChanged: {
                    currentLocality = currentItem.locality
                }

                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                delegate: ItemDelegate {
                    property Locality locality: Locality {
                        localityId: f_id
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
