import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import com.milk.core 1.0
import com.milk.db 1.0

Item {
    height: 200
    width: 160

    readonly property alias milkTable: proxy.sourceModel
    readonly property alias proxy: proxy
    readonly property alias viewModel: viewModel
    readonly property alias viewMenu: viewMenu
    readonly property alias viewFilter: textFieldFilterName
    property int currentMilkId: viewModel.currentItem._milkId

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
                id: viewMenu
                height: 40
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop

                RowLayout {
                    ToolButton {
                        Image {
                            source: "/img/locality/locality_add.png"
                            width:  32
                            height: 32
                        }

                        onClicked: {
                            dialogs.dialogAddEditLocality.openInsert()
                        }
                    }
                    ToolButton {
                        Image {
                            source: "/img/locality/locality_edit.png"
                            width:  32
                            height: 32
                        }

                        onClicked: {
                            dialogs.dialogAddEditLocality.openUpdate(currentMilkId)
                        }
                    }
                    ToolButton {
                        Image {
                            source: "/img/locality/locality_remove.png"
                            width:  32
                            height: 32
                        }

                        onClicked: {
                            dialogs.dialogRemoveLocality.milkId = currentMilkId
                            dialogs.dialogRemoveLocality.open()
                        }
                    }
                }
            }

            ListView {
                id: viewModel

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                Layout.minimumWidth: 100

                model: LocalitiesSortFilterProxyModel {
                    id: proxy
                    sourceModel: milkCore.db.localities
                    name: textFieldFilterName.text
                }

                remove: Transition {
                    ParallelAnimation {
                        NumberAnimation { property: "opacity"; to: 0; duration: 1000 }
                        NumberAnimation { properties: "x,y"; to: 100; duration: 1000 }
                    }
                }

                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                delegate: ItemDelegate {
                    text: model.name
                    property int _milkId: model.milkId
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
                        viewModel.forceActiveFocus()
                        viewModel.currentIndex = index
                    }
                }
            }
        }
    }

//    Connections {
//        target: milkCore.db
//        onLocalitiesChanged: viewModel.currentIndex = 0
//    }
}
