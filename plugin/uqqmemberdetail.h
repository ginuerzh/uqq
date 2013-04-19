#ifndef UQQMEMBERDETAIL_H
#define UQQMEMBERDETAIL_H

#include <QObject>
#include <QtQml>

class UQQMemberDetail : public QObject
{
    Q_OBJECT
public:

    enum Gender {
        Secret,
        Male,
        Female
    };

    static Gender genderIndex(const QString &s);

    Q_PROPERTY(quint64 account READ account NOTIFY accountChanged)

    Q_PROPERTY(int level READ level NOTIFY levelChanged)
    Q_PROPERTY(int levelDays READ levelDays NOTIFY levelDaysChanged)
    Q_PROPERTY(int levelHours READ levelHours NOTIFY levelHoursChanged)
    Q_PROPERTY(int levelRemainDays READ levelRemainDays NOTIFY levelRemainDaysChanged)

    Q_PROPERTY(QDateTime birthday READ birthday NOTIFY birthdayChanged)
    Q_PROPERTY(QString occupation READ occupation NOTIFY occupationChanged)
    Q_PROPERTY(QString phone READ phone NOTIFY phoneChanged)
    Q_PROPERTY(QString mobile READ mobile NOTIFY mobileChanged)
    Q_PROPERTY(bool allow READ allow NOTIFY allowChanged)
    Q_PROPERTY(QString college READ college NOTIFY collegeChanged)
    Q_PROPERTY(int shengxiao READ shengxiao NOTIFY shengxiaoChanged)
    Q_PROPERTY(int constel READ constel NOTIFY constelChanged)
    Q_PROPERTY(int blood READ blood NOTIFY bloodChanged)
    Q_PROPERTY(QString homepage READ homepage NOTIFY homepageChanged)
    Q_PROPERTY(QString country READ country NOTIFY countryChanged)
    Q_PROPERTY(QString province READ province NOTIFY provinceChanged)
    Q_PROPERTY(QString city READ city NOTIFY cityChanged)
    Q_PROPERTY(QString personal READ personal NOTIFY personalChanged)
    Q_PROPERTY(QString email READ email NOTIFY emailChanged)
    Q_PROPERTY(int gender READ gender NOTIFY genderChanged)
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged)

    explicit UQQMemberDetail(QObject *parent = 0);

    quint64 account() const;
    void setAccount(quint64 account);

    int level() const;
    void setLevel(int level);
    int levelDays() const;
    void setLevelDays(int days);
    int levelHours() const;
    void setLevelHours(int hours);
    int levelRemainDays() const;
    void setLevelRemainDays(int remainDays);

    // the member's detail
    int faceid() const;
    void setFaceid(int faceid);
    QDateTime birthday() const;
    void setBirthday(const QDateTime &birthday);
    QString occupation() const;
    void setOccupation(const QString &occupation);
    QString phone() const;
    void setPhone(const QString &phone);
    QString mobile() const;
    void setMobile(const QString &mobile);
    bool allow() const;
    void setAllow(bool allow);
    QString college() const;
    void setCollege(const QString &college);
    int shengxiao() const;
    void setShengxiao(int shengxiao);
    int constel() const;
    void setConstel(int constel);
    int blood() const;
    void setBlood(int blood);
    QString homepage() const;
    void setHomepage(const QString &homepage);
    QString country() const;
    void setCountry(const QString &country);
    QString province() const;
    void setProvince(const QString &province);
    QString city() const;
    void setCity(const QString &city);
    QString personal() const;
    void setPersonal(const QString &personal);
    QString email() const;
    void setEmail(const QString &email);
    int gender() const;
    void setGender(int gender);
    QString token() const;
    void setToken(const QString &token);
    
signals:
    void accountChanged();

    void levelChanged();
    void levelDaysChanged();
    void levelHoursChanged();
    void levelRemainDaysChanged();

    void birthdayChanged();
    void occupationChanged();
    void phoneChanged();
    void mobileChanged();
    void allowChanged();
    void collegeChanged();
    void shengxiaoChanged();
    void constelChanged();
    void bloodChanged();
    void homepageChanged();
    void countryChanged();
    void provinceChanged();
    void cityChanged();
    void personalChanged();
    void emailChanged();
    void genderChanged();
    void tokenChanged();

public slots:

private:
    quint64 m_account;

    int m_level;
    int m_levelDays;
    int m_levelHours;
    int m_levelRemainDays;

    int m_faceid;
    QDateTime m_birthday;
    QString m_occupation;
    QString m_phone;
    QString m_mobile;
    bool m_allow;
    QString m_college;
    int m_shengxiao;
    int m_constel;
    int m_blood;
    QString m_homepage;
    QString m_country;
    QString m_province;
    QString m_city;
    QString m_personal;
    QString m_email;
    int m_gender;
    QString m_token;
    
};

#endif // UQQMEMBERDETAIL_H
