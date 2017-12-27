import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0
import com.milk.db 1.0

Dialog {
    title: qsTr("Удаление молокопункта")
    modal: true
    standardButtons: Dialog.Ok

    property alias milkId: _item.milkId

    DbMilkPoint {
        id: _item
        model: milkCore.db.milkPoints

        onMilkIdChanged: _item.loadData(milkId)
    }

    Label{
        id: _content
    }

    onAccepted: {
        if (_item.milkId === -1) {
            console.log("MilkPoint is null")
            close()
            return
        }

        if (_item.remove()) {
            console.log(qsTr("Молокопункт успешно удалён"))
        }

        _item.reset()
    }

    onOpened: {
        if (_item.milkId === -1)
            _content.text = qsTr("Выберите молокопункт")
        else
            _content.text = "Вы действительно желаете удалить '" + _item.name + "'?\n" +
                    "Будут также удалены сдачи молока в этом молокопункте."
    }
}
