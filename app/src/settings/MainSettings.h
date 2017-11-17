#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QObject>


class MainSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastChoosenDb READ lastChoosenDb WRITE setLastChoosenDb NOTIFY lastChoosenDbChanged RESET resetLastChoosenDb)
    Q_PROPERTY(float priceLiter READ priceLiter WRITE setPriceLiter NOTIFY priceLiterChanged RESET resetPriceLiter)
    Q_PROPERTY(QString firmName READ firmName WRITE setFirmName NOTIFY firmNameChanged RESET resetFirmName)
    Q_PROPERTY(QString milkInspector READ milkInspector WRITE setMilkInspector NOTIFY milkInspectorChanged RESET resetMilkInspector)
    Q_PROPERTY(QString milkInspector2 READ milkInspector2 WRITE setMilkInspector2 NOTIFY milkInspector2Changed RESET resetMilkInspector2)
    Q_PROPERTY(bool isFetchTablesOnRefresh READ isFetchTablesOnRefresh WRITE setIsFetchTablesOnRefresh NOTIFY isFetchTablesOnRefreshChanged RESET resetFetchTablesOnRefresh)

public:
    explicit MainSettings(const QString &lastChoosenDb, const float priceLiter, const QString &firmName,
                          const QString &milkInspector, const QString &milkInspector_2,
                          const bool isFetchTablesOnRefresh = false, QObject *parent = Q_NULLPTR);
    explicit MainSettings(QObject *parent = Q_NULLPTR);
    virtual ~MainSettings();

    QString lastChoosenDb() const { return m_lastChoosenDb; }
    float priceLiter() const { return m_priceLiter; }
    QString firmName() const { return m_firmName; }
    QString milkInspector() const { return m_milkInspector; }
    QString milkInspector2() const { return m_milkInspector2; }
    bool isFetchTablesOnRefresh() const { return m_isFetchTablesOnRefresh; }

public slots:
    void setLastChoosenDb(const QString &lastChoosenDb);
    void setPriceLiter(float priceLiter);
    void setFirmName(const QString &firmName);
    void setMilkInspector(const QString &milkInspector);
    void setMilkInspector2(const QString &milkInspector2);
    void setIsFetchTablesOnRefresh(bool isFetchTablesOnRefresh);
    void reset();

signals:
    void lastChoosenDbChanged(QString lastChoosenDb);
    void priceLiterChanged(float priceLiter);
    void firmNameChanged(QString firmName);
    void milkInspectorChanged(QString milkInspector);
    void milkInspector2Changed(QString milkInspector2);
    void isFetchTablesOnRefreshChanged(bool isFetchTablesOnRefresh);

private:
    QString m_lastChoosenDb;
    float m_priceLiter;
    QString m_firmName;
    QString m_milkInspector;
    QString m_milkInspector2;
    bool m_isFetchTablesOnRefresh;

    void resetLastChoosenDb();
    void resetPriceLiter();
    void resetFirmName();
    void resetMilkInspector();
    void resetMilkInspector2();
    void resetFetchTablesOnRefresh();
};

#endif // MAINSETTINGS_H
