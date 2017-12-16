import QtQuick 2.9
import QtQuick.Controls 2.2
import com.milk.core 1.0

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
}
