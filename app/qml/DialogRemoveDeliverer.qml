import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0
import com.milk.db 1.0

Dialog {
    title: qsTr("Удаление сдатчика")
    modal: true
    standardButtons: Dialog.Ok

    property alias milkId: _item.milkId

    DbDeliverer {
        id: _item
        model: milkCore.db.deliverers

        onMilkIdChanged: _item.loadData(milkId)
    }

    Label{
        id: _content
    }

    onAccepted: {
        if (_item.milkId === -1) {
            console.log("Deliverer is null")
            close()
            return
        }

        if (_item.remove()) {
            console.log(qsTr("Сдатчик успешно удалён"))
            milkCore.db.milkReception.refresh()
        }

        _item.reset()
    }

    onOpened: {
        if (_item.milkId === -1)
            _content.text = qsTr("Выберите сдатчика")
        else
            _content.text = "Вы действительно желаете удалить '" + _item.fullName + "'?\n" +
                    "Будут также удалены сдачи молока, произведённые этим сдатчиком."
    }
}
