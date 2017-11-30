import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0

Item {
    property DialogAddEditLocality dialogAddEditLocality: DialogAddEditLocality { }
    property DialogRemoveLocality dialogRemoveLocality: DialogRemoveLocality {}

    property DialogRemoveMilkPoint dialogRemoveMilkPoint: DialogRemoveMilkPoint { }
    property DialogAddEditMilkPoint dialogAddEditMilkPoint: DialogAddEditMilkPoint {}

    property DialogRemoveDeliverer dialogRemoveDeliverer: DialogRemoveDeliverer {
        y: -height / 2
        x: -width / 2
    }
    property DialogAddEditDeliverer dialogAddEditDeliverer: DialogAddEditDeliverer {
        y: -height / 2
        x: -width / 2
    }
}
