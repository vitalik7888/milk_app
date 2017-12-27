import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0
import com.milk.db 1.0

Dialog {
    title: qsTr("Удаление населённого пункта")
    modal: true
    standardButtons: Dialog.Ok
    property alias milkId: _item.milkId

    DbLocality {
        id: _item
        model: milkCore.db.localities

        onMilkIdChanged: _item.loadData(milkId)
    }

    Label{
        id: _content
    }

    onAccepted: {
        if (_item.milkId === -1) {
            console.log("Locality is null")
            close()
            return
        }

        if (_item.remove()) {
            console.log(qsTr("Населенный пункт успешно удалён"))
        }

        _item.reset()
    }

    onOpened: {
        if (_item.milkId === -1)
            _content.text = qsTr("Выберите населённый пункт")
        else
            _content.text = "Вы действительно желаете удалить '" + _item.name + "'?\n" +
                    "Будут также удалены молокопункты и сдачи молока в этом населённом пункте."
    }
}
