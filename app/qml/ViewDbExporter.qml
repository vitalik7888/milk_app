import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import com.milk.plugins 1.0
import QtQuick.Dialogs 1.0

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

        ListView {
            id: viewTables
            width: parent.width
            height: 100

            model: milkCore.db.tables

            delegate: ItemDelegate {
                width: parent.width

                Row {
                    Label {
                        text: "item"
                    }
                    CheckBox {
                        checked: true
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
}
