import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0
import com.milk.db 1.0
import com.milk.types 1.0

Dialog {
    title: qsTr("Удаление молокопункта")
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

        if (milkCore.db.milkPoints.remove(row)) {
            console.log(qsTr("Молокопункт успешно удалён"))
            milkCore.db.milkReception.refresh()
        }
        row = -1
    }

    onOpened: {
        var _milkPoint = milkCore.db.milkPoints.get(row)
        if (_milkPoint == null)
            _content.text = qsTr("Выберите молокопункт")
        else
            _content.text = "Вы действительно желаете удалить '" + _milkPoint.name + "'?\n" +
                    "Будут также удалены сдачи молока в этом молокопункте."
    }
}
