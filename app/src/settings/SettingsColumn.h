#ifndef SETTINGSCOLUMN_H
#define SETTINGSCOLUMN_H

#include <QObject>

// TODO reset functions
class SettingsColumn : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString display READ display WRITE setDisplay NOTIFY displayChanged RESET resetDisplay)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged RESET resetType)
    Q_PROPERTY(int prec READ prec WRITE setPrec NOTIFY precChanged RESET resetPrec)
    Q_PROPERTY(bool isShow READ isShow WRITE setIsShow NOTIFY isShowChanged RESET resetIsShow)

public:
    explicit SettingsColumn(const QString display, const int type,
                            const int prec, bool isShow, QObject *parent = Q_NULLPTR);
    explicit SettingsColumn(QObject *parent = Q_NULLPTR);
    virtual ~SettingsColumn();

    QString display() const { return m_display; }
    int type() const { return m_type; }
    int prec() const { return m_prec; }
    bool isShow() const { return m_isShow; }

public slots:
    void setDisplay(QString display);
    void setType(int type);
    void setPrec(int prec);
    void setIsShow(bool isShow);
    void reset();

signals:
    void displayChanged(QString display);
    void typeChanged(int type);
    void precChanged(int prec);
    void isShowChanged(bool isShow);

private:
    QString m_display;
    int m_type;
    int m_prec;
    bool m_isShow;

    void resetDisplay();
    void resetType();
    void resetPrec();
    void resetIsShow();
};

#endif // SETTINGSCOLUMN_H
