#include "Test_SettingsColumn.h"

#include "SettingsColumn.h"
#include "SettingsConstants.h"
// Qt
#include <QTest>
#include <QSignalSpy>

using SC = SettingsConstants;
using SCCOL = SC::Column;


Test_SettingsColumn::Test_SettingsColumn(QObject *parent) : QObject(parent)
{

}

void Test_SettingsColumn::testEmptyConstructor()
{
    SettingsColumn sc;
    compareDefault(&sc);
}

void Test_SettingsColumn::testConstructor()
{
    SettingsColumn sc("display", 1, 2, false);
    compare(&sc, "display", 1, 2, false);
}

void Test_SettingsColumn::testMethods()
{
    SettingsColumn sc;
    sc.setDisplay("dis");
    sc.setType(2);
    sc.setPrec(1);
    sc.setIsShow(true);
    compare(&sc, "dis", 2, 1, true);
}

void Test_SettingsColumn::testReset()
{
    SettingsColumn sc;
    sc.setDisplay("dis");
    sc.setType(2);
    sc.setPrec(1);
    sc.setIsShow(true);
    sc.reset();
    compareDefault(&sc);
}

void Test_SettingsColumn::compare(SettingsColumn *sc, const QString display,
                                  const int type, const int prec, bool isShow)
{
    QCOMPARE(sc->display(), display);
    QCOMPARE(sc->type(), type);
    QCOMPARE(sc->prec(), prec);
    QCOMPARE(sc->isShow(), isShow);
}

void Test_SettingsColumn::compareDefault(SettingsColumn *sc)
{
    QCOMPARE(sc->display(),  SCCOL::DEF_DISPLAY);
    QCOMPARE(sc->type(),     SCCOL::DEF_TYPE);
    QCOMPARE(sc->prec(),     SCCOL::DEF_PREC);
    QCOMPARE(sc->isShow(),   SCCOL::DEF_IS_SHOW);
}

void Test_SettingsColumn::testSignalDisplayChanged()
{
    SettingsColumn sc;
    const QString data = "displayy";
    QSignalSpy signalSpy(&sc, &SettingsColumn::displayChanged);
    sc.setDisplay(data);
    sc.setDisplay(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}

void Test_SettingsColumn::testSignalTypeChanged()
{
    SettingsColumn sc;
    const int data = SCCOL::DEF_TYPE + 1;
    QSignalSpy signalSpy(&sc, &SettingsColumn::typeChanged);
    sc.setType(data);
    sc.setType(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toInt(), data);
}

void Test_SettingsColumn::testSignalPrecChanged()
{
    SettingsColumn sc;
    const int data = SCCOL::DEF_PREC + 1;
    QSignalSpy signalSpy(&sc, &SettingsColumn::precChanged);
    sc.setPrec(data);
    sc.setPrec(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toInt(), data);
}

void Test_SettingsColumn::testSignalIsShowChanged()
{
    SettingsColumn sc;
    const bool data = !SCCOL::DEF_IS_SHOW;
    QSignalSpy signalSpy(&sc, &SettingsColumn::isShowChanged);
    sc.setIsShow(data);
    sc.setIsShow(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toBool(), data);
}
