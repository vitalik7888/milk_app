import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import com.milk.core 1.0
import com.milk.types 1.0
import com.milk.db 1.0
import com.milk.settings 1.0

Item {
    readonly property alias milkTable: proxy.sourceModel
    property Locality currentMilkItem
    property alias filter: proxy.locality

    function currentSourceRow() {
        return proxy.sourceRow(view.currentIndex)
    }

    height: 200
    width: 160

    GroupBox {
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
            ToolBar {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop

                RowLayout {
                    ToolButton {
                        Image {
                            source: "/img/locality/locality_add.png"
                        }

                        onClicked: {
                            dialogs.dialogAddEditLocality.row = currentSourceRow()
                            dialogs.dialogAddEditLocality.openInsert()
                        }
                    }
                    ToolButton {
                        Image {
                            source: "/img/locality/locality_edit.png"
                        }

                        onClicked: {
                            dialogs.dialogAddEditLocality.row = currentSourceRow()
                            dialogs.dialogAddEditLocality.openUpdate()
                        }
                    }
                    ToolButton {
                        Image {
                            source: "/img/locality/locality_remove.png"
                        }

                        onClicked: {
                            dialogs.dialogRemoveLocality.row = currentSourceRow()
                            dialogs.dialogRemoveLocality.open()
                        }
                    }
                }
            }

            ListView {
                id: view

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                Layout.minimumWidth: 100

                model: LocalitiesSortFilterProxyModel {
                    id: proxy
                    sourceModel: milkCore.db.localities
                    enableLocalityDynamicFilter: true
                    locality.name: textFieldFilterName.text
                }

                onCurrentIndexChanged: {
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
        onLocalitiesChanged: view.currentIndex = 0
    }
}
