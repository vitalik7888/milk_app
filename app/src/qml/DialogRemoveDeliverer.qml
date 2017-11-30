import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0
import com.milk.db 1.0
import com.milk.types 1.0

Dialog {
    title: qsTr("Удаление сдатчика")
    modal: true
    standardButtons: Dialog.Ok

    property int row: -1

    Label{
        id: _content
    }

    onAccepted: {
        if (row == -1) {
            close()
            return
        }

        if (milkCore.db.deliverers.remove(row)) {
            console.log(qsTr("Сдатчик успешно удалён"))
        }
        row = -1
    }

    onOpened: {
        var _item = milkCore.db.deliverers.get(row)
        if (_item == null)
            _content.text = qsTr("Выберите сдатчика")
        else
            _content.text = "Вы действительно желаете удалить '" + _item.name + "'?\n" +
                    "Будут также удалены сдачи молока, произведённые этим сдатчиком."
    }
}
