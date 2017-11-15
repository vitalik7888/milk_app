import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import Milk.Core 1.0
import Milk.Database 1.0

ListView {
    id: root
    property Deliverer currentDeliverer

    model: DeliverersTable {
        id: modelDeliverers
    }

    onCurrentItemChanged: {
        currentDeliverer = currentItem.deliverer
    }

    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

    delegate: ItemDelegate {
        property Deliverer deliverer: Deliverer {
            delivererId: f_id
            name: f_name
            inn: f_inn
            address: f_address
            phoneNumber: f_phone_number
        }

        text: f_name
        width: parent.width

        contentItem: Text {
            text: parent.text
            font: parent.font
            color: parent.enabled ? parent.Material.primaryTextColor
                                  : parent.Material.hintTextColor
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
        }

        onClicked:  {
            root.forceActiveFocus()
            root.currentIndex = index
        }
    }

}