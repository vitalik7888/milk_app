import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Milk.Types 1.0
import Milk.Database 1.0

Page {
    RowLayout {
        anchors.fill: parent

        GroupBox {
            title: qsTr("Сдатчики")
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                ColumnLayout {
                    spacing: 4

                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignLeft

                    TextField {
                        id: textFieldFilterDelivererName
                        placeholderText: qsTr("Фильтр")
                        height: 40
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignTop
                    }

                    ViewDeliverers {
                        id: viewDeliverers
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignCenter
                    }
                }

                ColumnLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    TextField {
                        id: textFieldDelivererName
                        placeholderText: qsTr("ФИО")
                        Layout.fillWidth: true
                        text: viewDeliverers.currentDeliverer.name
                    }

                    Row {
                        spacing: 4

                        Button {
                            text: qsTr("Удалить")

                            onClicked: {
                                if (viewDeliverers.currentDeliverer === null)
                                    return

                                console.log("Clicked delete")
                            }
                        }
                        Button {
                            text: qsTr("Сохранить")

                            onClicked: {
                                if (viewDeliverers.currentDeliverer === null)
                                    return

                                console.log("Clicked save")
                            }
                        }
                    }
                }
            }
        }
    }
}
