import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0 as Lab10
import com.milk.core 1.0
import com.milk.types 1.0
import com.milk.settings 1.0

Dialog {
    id: root
    standardButtons: Dialog.Save
    modal: true
    height: 500
    width: 500

    onAccepted: {
        saveMainSettings()
        savePrintSettings()
        saveCalcSettings()
    }

    onOpened: {
        loadMainSettingsValues()
        loadPrintSettingsValues()
        loadCalcSettingsValues()
        enableMainSettingsButtons(false)
        enablePrintSettingsButtons(false)
        enableCalcSettingsButtons(false)
    }

    header: TabBar {
        id: bar
        height: 40
        currentIndex: 0

        TabButton {
            text: qsTr("Основные")
        }
        TabButton {
            text: qsTr("Печать")
        }
        TabButton {
            text: qsTr("Расчёты")
        }
    }

    SwipeView {
        anchors.fill: parent
        currentIndex: bar.currentIndex
        clip: true

        Page {
            id: mainSettingsPage

            header: ToolBar {
                height: 40

                Row {
                    ToolButton {
                        id: btnMainSettingsReset
                        text: qsTr("Сбросить")
                        onClicked: resetMainSettings()
                    }

                    ToolButton {
                        id: btnMainSettingsCancel
                        enabled: false
                        text: qsTr("Отменить")
                        onClicked: cancelChangedMainSettings()
                    }

                    ToolButton {
                        id: btnMainSettingsSave
                        enabled: false
                        text: qsTr("Сохранить")
                        onClicked: saveMainSettings()
                    }
                }
            }

            Grid {
                anchors.fill: parent
                columns: 2
                spacing: 2

                Label {
                    text: qsTr("Название фирмы")
                }
                TextField {
                    id: textFirmName
                    onTextChanged: enableMainSettingsButtons(true)
                }

                Label {
                    text: qsTr("Инспектор №1")
                }
                TextField {
                    id: textMilkInspector
                    onTextChanged: enableMainSettingsButtons(true)
                }

                Label {
                    text: qsTr("Инспектор №2")
                }
                TextField {
                    id: textMilkInspector2
                    onTextChanged: enableMainSettingsButtons(true)
                }
            }
        }

        Page {
            id: printSettingsPage

            header: ToolBar {
                height: 40

                Row {
                    ToolButton {
                        id: btnPrintSettingsReset
                        text: qsTr("Сбросить")
                        onClicked: resetPrintSettings()
                    }

                    ToolButton {
                        id: btnPrintSettingsCancel
                        enabled: false
                        text: qsTr("Отменить")
                        onClicked: cancelChangedPrintSettings()
                    }

                    ToolButton {
                        id: btnPrintSettingsSave
                        enabled: false
                        text: qsTr("Сохранить")
                        onClicked: savePrintSettings()
                    }
                }
            }

            ScrollView {
                clip: true
                anchors.fill: parent

                Grid {
                    anchors.fill: parent
                    columns: 2
                    spacing: 2

                    Label { id: labelTextFont; text: qsTr("Основной шрифт")
                        onFontChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelTextFont) }

                    Label { id: labelCaptionTextFont; text: qsTr("Шрифт надписи")
                        onFontChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelCaptionTextFont) }

                    Label { id: labelCaptionColor; text: qsTr("Цвет надписи")
                        onColorChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelCaptionColor) }

                    Label { text: qsTr("Ширина таблицы") }
                    SpinBox { id: spinBoxTableWidth; onValueChanged: enablePrintSettingsButtons(true)
                        from: 1; to: 200 }

                    Label { text: qsTr("Ширина рамки таблицы") }
                    SpinBox { id: spinBoxTableBorderWidth; onValueChanged: enablePrintSettingsButtons(true)
                        from: 1 }

                    Label { text: qsTr("Стиль рамки таблицы") }
                    SpinBox { id: spinBoxTableBorderStyle; onValueChanged: enablePrintSettingsButtons(true)
                        from: 1 }

                    Label { text: qsTr("Внутренний отступ ячейки") }
                    SpinBox { id: spinBoxCellSpacing; onValueChanged: enablePrintSettingsButtons(true) }

                    Label { text: qsTr("Внешний отступ ячейки") }
                    SpinBox { id: spinBoxCellPadding; onValueChanged: enablePrintSettingsButtons(true) }

                    Label { id: labelTableBorderColor; text: qsTr("Цвет рамки таблицы")
                        onColorChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelTableBorderColor) }

                    Label { id: labelTableHeaderFont; text: qsTr("Шрифт заголовка таблицы")
                        onFontChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelTableHeaderFont) }

                    Label { id: labelTableHeaderColor; text: qsTr("Цвет заголовка таблицы")
                        onColorChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelTableHeaderColor) }

                    Label { id: labelTableTextFont; text: qsTr("Шрифт таблицы")
                        onFontChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelTableTextFont) }

                    Label { id: labelTableTextColor; text: qsTr("Цвет текста таблицы")
                        onColorChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelTableTextColor) }

                    Label { id: labelTableResultFont; text: qsTr("Шрифт результата таблицы")
                        onFontChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelTableResultFont) }

                    Label { id: labelTableResultColor; text: qsTr("Цвет результата таблицы")
                        onColorChanged: enablePrintSettingsButtons(true) }
                    ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelTableResultColor) }
                }

            }
        }
        Page {
            id: calcSettingsPage

            header: ToolBar {
                height: 40

                Row {
                    ToolButton {
                        id: btnCalcSettingsReset
                        text: qsTr("Сбросить")
                        onClicked: resetCalcSettings()
                    }

                    ToolButton {
                        id: btnCalcSettingsCancel
                        enabled: false
                        text: qsTr("Отменить")
                        onClicked: cancelChangedCalcSettings()
                    }

                    ToolButton {
                        id: btnCalcSettingsSave
                        enabled: false
                        text: qsTr("Сохранить")
                        onClicked: saveCalcSettings()
                    }
                }
            }

            Grid {
                anchors.fill: parent
                columns: 2
                spacing: 2

                Label { id: labelCalcTextFont; text: qsTr("Основной шрифт")
                    onFontChanged: enableCalcSettingsButtons(true) }
                ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelCalcTextFont) }

                Label { id: labelCalcTextBackColor; text: qsTr("Цвет фона")
                    onColorChanged: enableCalcSettingsButtons(true) }
                ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelCalcTextBackColor) }

                Label { id: labelCalcDelivResFont; text: qsTr("Шрифт сдатчика")
                    onFontChanged: enableCalcSettingsButtons(true) }
                ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelCalcDelivResFont) }

                Label { id: labelCalcDelivResColor; text: qsTr("Цвет сдатчика")
                    onColorChanged: enableCalcSettingsButtons(true) }
                ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelCalcDelivResColor) }

                Label { id: labelCalcAllResFont; text: qsTr("Шрифт всех сдатчиков")
                    onFontChanged: enableCalcSettingsButtons(true) }
                ToolButton { text: "..."; onClicked: dialogChooseFont.openWithItem(labelCalcAllResFont) }

                Label { id: labelCalcAllResColor; text: qsTr("Цвет всех сдатчиков")
                    onColorChanged: enableCalcSettingsButtons(true) }
                ToolButton { text: "..."; onClicked: dialogChooseColor.openWithItem(labelCalcAllResColor) }

                Label { text: qsTr("Формат даты") }
                TextField { id: textDateFormat; onTextChanged: enableCalcSettingsButtons(true) }
            }
        }
    }

    // Main
    function resetMainSettings() {
        milkCore.settings.main.reset()
        loadMainSettingsValues()
        enableMainSettingsButtons(false)
    }

    function cancelChangedMainSettings() {
        milkCore.settings.readMainSettings()
        loadMainSettingsValues()
        enableMainSettingsButtons(false)
    }

    function saveMainSettings() {
        milkCore.settings.main.firmName = textFirmName.text
        milkCore.settings.main.milkInspector = textMilkInspector.text
        milkCore.settings.main.milkInspector2 = textMilkInspector2.text
        milkCore.settings.writeMainSettings()
        enableMainSettingsButtons(false)
    }

    function loadMainSettingsValues() {
        textFirmName.text = milkCore.settings.main.firmName
        textMilkInspector.text = milkCore.settings.main.milkInspector
        textMilkInspector2.text = milkCore.settings.main.milkInspector2
    }

    function enableMainSettingsButtons(_enable) {
        btnMainSettingsCancel.enabled = _enable
        btnMainSettingsSave.enabled = _enable
    }

    // Print
    function resetPrintSettings() {
        milkCore.settings.print.reset()
        loadPrintSettingsValues()
        enablePrintSettingsButtons(false)
    }

    function cancelChangedPrintSettings() {
        milkCore.settings.readPrintSettings()
        loadPrintSettingsValues()
        enablePrintSettingsButtons(false)
    }

    function savePrintSettings() {
        milkCore.settings.print.textFont = labelTextFont.font
        milkCore.settings.print.captionTextFont = labelCaptionTextFont.font
        milkCore.settings.print.captionColor = labelCaptionColor.color
        milkCore.settings.print.tableWidth = spinBoxTableWidth.value
        milkCore.settings.print.tableBorderWidth = spinBoxTableBorderWidth.value
        milkCore.settings.print.tableBorderStyle = spinBoxTableBorderStyle.value
        milkCore.settings.print.cellSpacing = spinBoxCellSpacing.value
        milkCore.settings.print.cellPadding = spinBoxCellPadding.value
        milkCore.settings.print.tableBorderColor = labelTableBorderColor.color
        milkCore.settings.print.tableHeaderFont = labelTableHeaderFont.font
        milkCore.settings.print.tableHeaderColor = labelTableHeaderColor.color
        milkCore.settings.print.tableTextFont = labelTableTextFont.font
        milkCore.settings.print.tableTextColor = labelTableTextColor.color
        milkCore.settings.print.tableResultFont = labelTableResultFont.font
        milkCore.settings.print.tableResultColor = labelTableResultColor.color
        enablePrintSettingsButtons(false)
    }

    function loadPrintSettingsValues() {
        labelTextFont.font = milkCore.settings.print.textFont
        labelCaptionTextFont.font = milkCore.settings.print.captionTextFont
        labelCaptionColor.color = milkCore.settings.print.captionColor
        spinBoxTableWidth.value = milkCore.settings.print.tableWidth
        spinBoxTableBorderWidth.value = milkCore.settings.print.tableBorderWidth
        spinBoxTableBorderStyle.value = milkCore.settings.print.tableBorderStyle
        spinBoxCellSpacing.value = milkCore.settings.print.cellSpacing
        spinBoxCellPadding.value = milkCore.settings.print.cellPadding
        labelTableBorderColor.color = milkCore.settings.print.tableBorderColor
        labelTableHeaderFont.font = milkCore.settings.print.tableHeaderFont
        labelTableHeaderColor.color = milkCore.settings.print.tableHeaderColor
        labelTableTextFont.font = milkCore.settings.print.tableTextFont
        labelTableTextColor.color = milkCore.settings.print.tableTextColor
        labelTableResultFont.font = milkCore.settings.print.tableResultFont
        labelTableResultColor.color = milkCore.settings.print.tableResultColor
    }

    function enablePrintSettingsButtons(_enable) {
        btnPrintSettingsCancel.enabled = _enable
        btnPrintSettingsSave.enabled = _enable
    }

    // Calc
    function resetCalcSettings() {
        milkCore.settings.calc.reset()
        loadCalcSettingsValues()
        enableCalcSettingsButtons(false)
    }

    function cancelChangedCalcSettings() {
        milkCore.settings.readCalcSettings()
        loadCalcSettingsValues()
        enableCalcSettingsButtons(false)
    }

    function saveCalcSettings() {
        milkCore.settings.calc.textFont = labelCalcTextFont.font
        milkCore.settings.calc.textBackColor = labelCalcTextBackColor.color
        milkCore.settings.calc.delivResultFont = labelCalcDelivResFont.font
        milkCore.settings.calc.delivResultColor = labelCalcDelivResColor.color
        milkCore.settings.calc.allResultFont = labelCalcAllResFont.font
        milkCore.settings.calc.allResultColor = labelCalcAllResColor.color
        milkCore.settings.calc.dateFormat = textDateFormat.text
        enablePrintSettingsButtons(false)
    }

    function loadCalcSettingsValues() {
        labelCalcTextFont.font = milkCore.settings.calc.textFont
        labelCalcTextBackColor.color = milkCore.settings.calc.textBackColor
        labelCalcDelivResFont.font = milkCore.settings.calc.delivResultFont
        labelCalcDelivResColor.color = milkCore.settings.calc.delivResultColor
        labelCalcAllResFont.font = milkCore.settings.calc.allResultFont
        labelCalcAllResColor.color = milkCore.settings.calc.allResultColor
        textDateFormat.text = milkCore.settings.calc.dateFormat
    }

    function enableCalcSettingsButtons(_enable) {
        btnCalcSettingsCancel.enabled = _enable
        btnCalcSettingsSave.enabled = _enable
    }

    Lab10.FontDialog {
        id: dialogChooseFont
        title: qsTr("Выбор шрифта")
        modality: Qt.WindowModal
        property Item itemForSavingFont // FIXME

        onAccepted: {
            itemForSavingFont.font = dialogChooseFont.font
            itemForSavingFont = null
        }

        function openWithItem(_item) {
            dialogChooseFont.itemForSavingFont = _item
            dialogChooseFont.open()
        }
    }

    Lab10.ColorDialog {
        id: dialogChooseColor
        title: qsTr("Выбор шрифта")
        modality: Qt.WindowModal
        property Item itemForSavingColor // FIXME

        onAccepted: {
            itemForSavingColor.color = dialogChooseColor.color
            itemForSavingColor = null
        }

        function openWithItem(_item) {
            dialogChooseColor.itemForSavingColor = _item
            dialogChooseColor.open()
        }
    }
}
