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
    height: 300
    readonly property alias viewLocalities: viewLocalities

    onAccepted: {
        if (textFieldName.text === "") {
            errors.text = qsTr("Заполните название")
            open()
            return
        }
        if (_milkPoint.locality === null) {
            errors.text = qsTr("Выберите населённый пункт")
            open()
            return
        }

        if (_milkPoint.milkPointId === -1) {
            if (milkCore.db.milkPoints.append(_milkPoint))
                console.log(qsTr("Молокопункт успешно добавлен"))
        } else {
            if (milkCore.db.milkPoints.set(row, _milkPoint))
                console.log(qsTr("Молокопункт успешно сохранён"))
        }
    }

    MilkPoint {
        id: _milkPoint
        milkPointId: spinBoxMilkPointId.value
        locality: viewLocalities.currentMilkItem
        name: textFieldName.text
        description: textFieldDescription.text
    }

    GridLayout {
        anchors.fill: parent
        columns: 2
        rows: 3

        ViewLocalities {
            id: viewLocalities
            Layout.rowSpan: 3
            Layout.fillHeight: true
            Layout.fillWidth: true
            viewMenu.visible: false
        }

        SpinBox {
            id: spinBoxMilkPointId
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
        spinBoxMilkPointId.visible = true
        viewLocalities.filter.reset()

        var obj = milkCore.db.milkPoints.get(row)
        if (obj == null) {
            close()
            return
        }
        spinBoxMilkPointId.value = obj.milkPointId
        textFieldName.text = obj.name
        textFieldDescription.text = obj.description
        viewLocalities.viewTable.currentIndex = viewLocalities.proxy.findRowById(obj.locality.localityId)

        open()
    }

    function openInsert() {
        errors.text = ""
        spinBoxMilkPointId.value = -1
        textFieldName.text = ""
        textFieldDescription.text = ""
        spinBoxMilkPointId.visible = false

        open()
    }
}
