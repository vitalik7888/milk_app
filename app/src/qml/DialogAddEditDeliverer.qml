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
    height: 400
    readonly property alias viewLocalities: viewLocalities

    onAccepted: {
        if (!check()) {
            open()
            return
        }

        if (_deliverer.delivererId === -1) {
            if (milkCore.db.deliverers.append(_deliverer))
                console.log(qsTr("Сдатчик успешно добавлен"))
        } else {
            if (milkCore.db.deliverers.set(row, _deliverer))
                console.log(qsTr("Сдатчик успешно сохранён"))
        }
    }

    Deliverer {
        id: _deliverer
        delivererId: spinBoxDelivererId.value
        name: textFieldName.text
        inn: textFieldInn.text
        locality: viewLocalities.currentMilkItem
        address: textFieldAddress.text
        phoneNumber: textFieldPhoneNumber.text
    }

    GridLayout {
        anchors.fill: parent
        columns: 2
        rows: 6

        ViewLocalities {
            id: viewLocalities
            Layout.rowSpan: 6
            Layout.fillHeight: true
            Layout.fillWidth: true
            viewMenu.visible: false
        }

        SpinBox {
            id: spinBoxDelivererId
            enabled: false
            from: -1
            to: 9999
        }

        TextField {
            id: textFieldName
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Фио")
            font.capitalization: Font.Capitalize
        }
        TextField {
            id: textFieldInn
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Инн")
            font.capitalization: Font.Capitalize
        }
        TextField {
            id: textFieldAddress
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Адрес")
            font.capitalization: Font.Capitalize
        }
        TextField {
            id: textFieldPhoneNumber
            Layout.fillWidth: true
            height: 80
            placeholderText: qsTr("Номер телефона")
            font.capitalization: Font.Capitalize
        }
        Label {
            id: errors
            color: "red"
        }
    }

    function openUpdate() {
        errors.text = ""
        spinBoxDelivererId.visible = true
        viewLocalities.filter.reset()

        var obj = milkCore.db.deliverers.get(row)
        if (obj == null) {
            close()
            return
        }
        spinBoxDelivererId.value = obj.delivererId
        textFieldName.text = obj.name
        textFieldAddress.text = obj.address
        textFieldInn.text = obj.inn
        textFieldPhoneNumber.text = obj.phoneNumber
        viewLocalities.viewTable.currentIndex = viewLocalities.proxy.findRowById(obj.locality.localityId)

        open()
    }

    function openInsert() {
        errors.text = ""
        spinBoxDelivererId.value = -1
        textFieldName.text = ""
        textFieldAddress.text = ""
        spinBoxDelivererId.visible = false

        open()
    }

    function check() {
        if (_deliverer.name === "") {
            errors.text = qsTr("Заполните фио")
            return false
        }
        if (_deliverer.locality == null) {
            errors.text = qsTr("Выберите населённый пункт")
            return false
        }

        return true
    }
}
