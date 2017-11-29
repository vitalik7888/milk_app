import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import com.milk.core 1.0
import com.milk.types 1.0
import com.milk.db 1.0

Item {
    readonly property alias milkTable: proxy.sourceModel
    property Deliverer currentMilkItem
    property alias filter: proxy.deliverer

    function currentSourceRow() {
        return proxy.sourceRow(view.currentIndex)
    }

    height: 200
    width: 160

    GroupBox {
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

            ToolBar {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop

                RowLayout {
                    ToolButton {
                        Image {
                            source: "/img/user/user_add.png"
                            width:  32
                            height: 32
                        }

                        onClicked: {
                            dialogs.dialogAddEditDeliverer.row = currentSourceRow()
                            dialogs.dialogAddEditDeliverer.openInsert()
                        }
                    }
                    ToolButton {
                        Image {
                            source: "/img/user/user_edit.png"
                            width:  32
                            height: 32
                        }

                        onClicked: {
                            dialogs.dialogAddEditDeliverer.row = currentSourceRow()
                            dialogs.dialogAddEditDeliverer.openUpdate()
                        }
                    }
                    ToolButton {
                        Image {
                            source: "/img/user/user_remove.png"
                            width:  32
                            height: 32
                        }

                        onClicked: {
                            dialogs.dialogRemoveDeliverer.row = currentSourceRow()
                            dialogs.dialogRemoveDeliverer.open()
                        }
                    }
                }
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

                onCurrentItemChanged: {
                    currentMilkItem = milkTable.get(currentIndex)
                }

                remove: Transition {
                    ParallelAnimation {
                        NumberAnimation { property: "opacity"; to: 0; duration: 1000 }
                        NumberAnimation { properties: "x,y"; to: 100; duration: 1000 }
                    }
                }

                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                delegate: ItemDelegate {
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

    Connections {
        target: milkCore.db
        onDeliverersChanged: view.currentIndex = 0
    }
}
