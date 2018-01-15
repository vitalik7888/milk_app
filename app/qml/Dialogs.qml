import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3
import com.milk.core 1.0
import com.milk.db 1.0

Item {
    property DialogAddEditLocality dialogAddEditLocality: DialogAddEditLocality {
        y: -height / 2
        x: -width / 2
    }
    property DialogRemoveLocality dialogRemoveLocality: DialogRemoveLocality {
        y: -height / 2
        x: -width / 2
    }

    property DialogRemoveMilkPoint dialogRemoveMilkPoint: DialogRemoveMilkPoint {
        y: -height / 2
        x: -width / 2
    }
    property DialogAddEditMilkPoint dialogAddEditMilkPoint: DialogAddEditMilkPoint {
        y: -height / 2
        x: -width / 2
    }

    property DialogRemoveDeliverer dialogRemoveDeliverer: DialogRemoveDeliverer {
        y: -height / 2
        x: -width / 2
    }
    property DialogAddEditDeliverer dialogAddEditDeliverer: DialogAddEditDeliverer {
        y: -height / 2
        x: -width / 2
    }

    property MessageDialog messageDialog: MessageDialog {
        function showInfo(infoDescription) {
            messageDialog.text = infoDescription
            messageDialog.icon = StandardIcon.Information
            messageDialog.open()
        }

        function showWarning(warningDescription) {
            messageDialog.text = warningDescription
            messageDialog.icon = StandardIcon.Warning
            messageDialog.open()
        }

        function showError(errorDescription) {
            messageDialog.text = errorDescription
            messageDialog.icon = StandardIcon.Critical
            messageDialog.open()
        }
    }

    property MessageDialog dbErrorsDialog: MessageDialog {
        icon: StandardIcon.Critical
    }

    property FileDialog fileDialogChooseDb: FileDialog {
        title: qsTr("Укажите базу данных")
        selectMultiple: false

        onAccepted: {
            milkCore.db.openDb(fileUrl.toString().replace("file://", ""))
        }
    }
}
