import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import Milk.Types 1.0
import Milk.Database 1.0

ListView {
    id: root
    property MilkPoint currentMilkPoint

    onCurrentItemChanged: {
        currentMilkPoint = currentItem.milkPoint
    }

    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

    delegate: ItemDelegate {
        property MilkPoint milkPoint: MilkPoint {
            milkPointId: f_id
            name: f_name
            description: f_description
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
