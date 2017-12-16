import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.milk.core 1.0
import com.milk.types 1.0

Dialog {
    id: root
    standardButtons: Dialog.Save | Dialog.Cancel
    modal: true
    property int row: -1

    onAccepted: {
        if (textFieldName.text === "") {
            errors.text = qsTr("Заполните название")
            open()
            return
        }

        if (_locality.localityId === -1) {
            if (milkCore.db.localities.append(_locality))
                console.log(qsTr("Населённый пункт успешно добавлен"))
        } else {
            if (milkCore.db.localities.set(row, _locality))
                console.log(qsTr("Населённый пункт успешно сохранён"))
        }
    }

    Locality {
        id: _locality
        localityId: spinBoxLocalityId.value
        name: textFieldName.text
        description: textFieldDescription.text
    }

    ColumnLayout {
        anchors.fill: parent

        SpinBox {
            id: spinBoxLocalityId
            enabled: false
            from: -1
            to: 9999

        }

        TextField {
            id: textFieldName
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Название")
            font.capitalization: Font.Capitalize
        }

        TextField {
            id: textFieldDescription
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

    function openUpdate() {
        errors.text = ""
        spinBoxLocalityId.visible = true

        var obj = milkCore.db.localities.get(row)
        if (obj == null) {
            close()
            return
        }
        spinBoxLocalityId.value = obj.localityId
        textFieldName.text = obj.name
        textFieldDescription.text = obj.description

        open()
    }

    function openInsert() {
        errors.text = ""
        spinBoxLocalityId.value = -1
        textFieldName.text = ""
        textFieldDescription.text = ""
        spinBoxLocalityId.visible = false

        open()
    }
}
