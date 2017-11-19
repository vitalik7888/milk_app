#ifndef TEST_SETTINGS_H
#define TEST_SETTINGS_H

#include <QObject>

class Settings;


class Test_Settings : public QObject
{
    Q_OBJECT
public:
    explicit Test_Settings(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void testEmptyConstructor();
    void testReadWriteDefaultSettings();
    void testReadWriteSettings();
    void testReadWriteSettingsAfterReset();

private:
    Settings *m_settings;
};

#endif // TEST_SETTINGS_H
