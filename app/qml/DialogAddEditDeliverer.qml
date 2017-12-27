import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.milk.core 1.0
import com.milk.db 1.0

Dialog {
    id: root
    standardButtons: Dialog.Save | Dialog.Cancel
    modal: true
    height: 400

    onAccepted: {
        if (!check()) {
            open()
            return
        }

        if (_item.milkId === -1) {
            if (_item.append())
                console.log(qsTr("Сдатчик успешно добавлен"))
        } else {
            if (_item.save())
                console.log(qsTr("Сдатчик успешно сохранён"))
        }
    }

    DbDeliverer {
        id: _item
        model: milkCore.db.deliverers
        firstName: textFieldFirstName.text
        lastName: textFieldLastName.text
        inn: textFieldInn.text
        address: textFieldAddress.text
        phoneNumber: textFieldPhoneNumber.text
    }

    GridLayout {
        anchors.fill: parent
        columns: 2

        ViewLocalities {
            id: viewLocalities
            Layout.rowSpan: 6
            Layout.fillHeight: true
            Layout.fillWidth: true
            viewMenu.visible: false

            onCurrentMilkIdChanged: _item.locality.loadData(viewLocalities.currentMilkId)
        }

        TextField {
            id: textFieldFirstName
            text: _item.firstName
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Имя")
            font.capitalization: Font.Capitalize
        }
        TextField {
            id: textFieldLastName
            text: _item.lastName
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Фамилия")
            font.capitalization: Font.Capitalize
        }
        TextField {
            id: textFieldInn
            text: _item.inn
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Инн")
            font.capitalization: Font.Capitalize
        }
        TextField {
            id: textFieldAddress
            text: _item.address
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Адрес")
            font.capitalization: Font.Capitalize
        }
        TextField {
            id: textFieldPhoneNumber
            text: _item.phoneNumber
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Номер телефона")
            font.capitalization: Font.Capitalize
        }
        Label {
            id: _errors
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

    onClosed: _errors.text = ""

    function check() {
        if (_item.lastName === "") {
            _errors.text = qsTr("Заполните фамилию")
            return false
        }

        if (_item.locality.milkId === -1) {
            _errors.text = qsTr("Выберите населённый пункт")
            return false
        }

        _errors.text = ""
        return true
    }
}
