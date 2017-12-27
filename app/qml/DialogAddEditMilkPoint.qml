import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.milk.core 1.0
import com.milk.db 1.0

Dialog {
    id: root
    modal: true
    height: 300
    standardButtons: Dialog.Save | Dialog.Cancel

    onAccepted: {
        if (!check()) {
            open()
            return
        }

        if (_item.milkId === -1) {
            if (_item.append())
                console.log(qsTr("Молокопункт успешно добавлен"))
        } else {
            if (_item.save())
                console.log(qsTr("Молокопункт успешно сохранён"))
        }
    }

    DbMilkPoint {
        id: _item
        model: milkCore.db.milkPoints
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

            onCurrentMilkIdChanged: _item.locality.loadData(viewLocalities.currentMilkId)
        }

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
        viewLocalities.proxy.resetFilter()
        _item.loadData(_milkId)
        viewLocalities.viewModel.currentIndex = _item.model.getPositionById(_item.locality.milkId)

        open()
    }

    function openInsert() {
        _item.reset()
        viewLocalities.viewModel.currentIndex = -1

        open()
    }

    function check()
    {
        if (textFieldName.text === "") {
            errors.text = qsTr("Заполните название")
            return false
        }
        if (_item.locality.milkId === -1) {
            errors.text = qsTr("Выберите населённый пункт")
            return false
        }

        errors.text = ""
        return true
    }
}
