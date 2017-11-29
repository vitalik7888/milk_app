import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0

Item {
    property DialogAddEditLocality dialogAddEditLocality: DialogAddEditLocality {}

    property Dialog dialogRemoveLocality: Dialog {
        title: qsTr("Удаление населённого пункта")
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

            if (milkCore.db.localities.remove(row)) {
                console.log(qsTr("Населенный пункт успешно удалён"))
                milkCore.db.deliverers.refresh()
                milkCore.db.milkPoints.refresh()
            }
            row = -1
        }

        onRejected: console.log("Delete Locality canceled")

        onOpened: {
            var _locality = milkCore.db.localities.get(row)
            if (_locality == null)
                _content.text = qsTr("Выберите населённый пункт")
            else
                _content.text = "Вы действительно желаете удалить '" + _locality.name + "'?\n" +
                        "Будут также удалены молокопункты и сдачи молока в этом населённом пункте."
        }
    }
}
