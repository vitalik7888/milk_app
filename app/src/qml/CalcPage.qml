import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4

Page {
    property alias tableViewCalc: tableViewCalc

    ColumnLayout {
        anchors.fill: parent
        spacing: 2

        GroupBox {
            id: groupBoxCriteria
            title: qsTr("Критерии")

            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
        }

        // TODO CalcModel for TreeView
        TableView {
            id: tableViewCalc

            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true

            TableViewColumn {
                role: "name"
                title: qsTr("Сдатчик")
                width: 200
            }
            TableViewColumn {
                role: "liters"
                title: qsTr("Литры")
                width: 100
            }
        }

        GroupBox {
            id: groupBoxBottom

            Layout.alignment: Qt.AlignBottom
            Layout.fillWidth: true

            Button {
                id: buttonCalc

                text: qsTr("Расчёты")
            }
        }
    }
}
