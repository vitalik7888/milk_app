import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.milk.core 1.0
import com.milk.db 1.0

Dialog {
    id: root
    standardButtons: Dialog.Save | Dialog.Cancel
    modal: true

    onAccepted: {
        if (textFieldName.text === "") {
            errors.text = qsTr("Заполните название")
            open()
            return
        }

        if (_item.milkId === -1) {
            if (_item.append())
                console.log(qsTr("Населённый пункт успешно добавлен"))
        } else {
            if (_item.save())
                console.log(qsTr("Населённый пункт успешно сохранён"))
        }
    }

    DbLocality {
        id: _item
        model: milkCore.db.localities
        name: textFieldName.text
        description: textFieldDescription.text
    }

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: textFieldName
            text: _item.name
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Название")
            font.capitalization: Font.Capitalize
        }

        TextField {
            id: textFieldDescription
            text: _item.description
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Описание")
            font.capitalization: Font.Capitalize
        }
        Label {
            id: errors
            color: "red"
        }
    }

    function openUpdate(_milkId) {
        errors.text = ""

        _item.loadData(_milkId)
        open()
    }

    function openInsert() {
        errors.text = ""
        _item.reset()

        open()
    }
}
