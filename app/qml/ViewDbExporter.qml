import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import com.milk.core 1.0
import com.milk.types 1.0
import com.milk.db 1.0
import com.milk.plugins 1.0

Popup {
    id: popup
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    Column {
        anchors.fill: parent
        spacing: 4

        Label {
            text: qsTr("Экспорт бд")
        }

        GroupBox {
            title: qsTr("Таблицы")
            height: 160
            width: parent.width

            ListView {
                id: viewTables
                anchors.fill: parent

                model: ListModel {

                }

                delegate: ItemDelegate {
                    width: parent.width
                    height: 30

                    Row {
                        Label {
                            text: tableName

                        }
                        CheckBox {
                            checked: isChoosen
                            onCheckedChanged: isChoosen = checked
                        }
                    }
                }
            }
        }

        Row {
            Label {
                text: qsTr("Тип")
            }
            ComboBox {
                id: comboBoxMode
                model: milkCore.plugins.dbExporter.types
            }
        }

        Row {
            TextField {
                id: textFieldFilePath
                placeholderText: qsTr("Путь к файлу")
            }
            ToolButton {
                text: "..."
                onClicked: fileDialog.open()
            }
        }
        Label {
            id: labelErrors
            color: "red"
        }

        Button {
            text: qsTr("Экспорт")

            onClicked: {
                if (!textFieldFilePath.text) {
                    labelErrors.text = qsTr("Укажите путь к файлу")
                    return
                }

                milkCore.plugins.dbExporter.filePath = textFieldFilePath.text
                milkCore.plugins.dbExporter.type = comboBoxMode.currentText
                for (var i = 0; i < viewTables.count; ++i) {
                    var tableItem = viewTables.model.get(i)
                    if (tableItem.isChoosen)
                        milkCore.plugins.dbExporter.tables.push(tableItem.tableName)
                }

                milkCore.plugins.dbExporter.dump()
            }
        }
    }

    onOpened: labelErrors.text = ""

    FileDialog {
        id: fileDialog
        title: qsTr("Выберите файл")
        folder: shortcuts.home
        onAccepted: {
            textFieldFilePath.text = fileDialog.fileUrl
        }
    }

    Component.onCompleted:  {
        for (var i = 0; i < milkCore.db.tables.length; ++i) {
            viewTables.model.append({tableName: milkCore.db.tables[i].tableName, isChoosen: true})
        }
    }
}
