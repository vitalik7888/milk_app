import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import Milk.Core 1.0
import Milk.Settings 1.0
import Milk.Database 1.0

Page {
    property alias buttonAddMilkReception: buttonAddMilkReception

    RowLayout {
        anchors.fill: parent
        spacing: 4

        LocalitiesSortFilterProxyModel {
            id: localitiesProxy
        }

        MilkPointsSortFilterProxyModel {
            id: milkPointsProxy

            milkPoint.locality.localityId: listViewCalcLocalities.currentLocality.localityId
        }

        DeliverersSortFilterProxyModel {
            id: deliverersProxy

            deliverer.locality.localityId: listViewCalcLocalities.currentLocality.localityId
        }

        ListViewLocalities {
            id: listViewCalcLocalities

            Layout.fillHeight: true
            Layout.minimumWidth: 100
        }

        ListViewMilkPoints {
            id: listViewCalcMilkPoints

            Layout.fillHeight: true
            Layout.minimumWidth: 100
        }

        ListViewDeliverers {
            id: listViewCalcDeliverers

            Layout.fillHeight: true
            Layout.minimumWidth: 100
        }

        GroupBox {
            id: groupBoxCalcOther

            Layout.alignment: Qt.AlignRight
            Layout.fillHeight: true
            Layout.minimumWidth: 100

            Grid {
                columns: 2

                Text {
                    text: qsTr("Цена")
                }

                SpinBox {
                    id: spinBox

                    decimals: 2
                    value: 0.0
                }

                Button {
                    id: buttonAddMilkReception
                    text: qsTr("Внести")

                    Layout.alignment: Qt.AlignBottom
                    Layout.fillWidth: true
                }
            }
        }
    }

    Connections {
        target: db
        onDbOpened: {
            localitiesProxy.enableDelivererDynamicFilter(true)
            milkPointsProxy.enableMilkPointDynamicFilter(true)
            deliverersProxy.enableDelivererDynamicFilter(true)

            localitiesProxy.sourceModel = db.localities
            listViewCalcLocalities.model = localitiesProxy

            milkPointsProxy.sourceModel = db.milkPoints
            listViewCalcMilkPoints.model = milkPointsProxy

            deliverersProxy.sourceModel = db.deliverers
            listViewCalcDeliverers.model = deliverersProxy
        }
    }
}
