#ifndef UQQMEMBER_H
#define UQQMEMBER_H

#include <QObject>
#include <QUrl>

class UQQMember : public QObject
{
    Q_OBJECT
public:

    enum Status {
        OnlineStatus,
        CallmeStatus,
        BusyStatus,
        AwayStatus,
        SilentStatus,
        HiddenStatus,
        OfflineStatus
    };

    enum Gender {
        Secret,
        Male,
        Female
    };

    static Status statusIndex(const QString &s);
    static Gender genderIndex(const QString &s);

    Q_PROPERTY(QString uin READ uin NOTIFY uinChanged)
    Q_PROPERTY(QString account READ account NOTIFY accountChanged)
    Q_PROPERTY(int category READ category NOTIFY categoryChanged)
    Q_PROPERTY(QString markname READ markname NOTIFY marknameChanged)
    Q_PROPERTY(QString nickname READ nickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString longnick READ longnick NOTIFY longnickChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QUrl face READ face NOTIFY faceChanged)
    Q_PROPERTY(bool isVip READ isVip NOTIFY vipChanged)
    Q_PROPERTY(int vipLevel READ vipLevel NOTIFY vipLevelChanged)

    Q_PROPERTY(int level READ level NOTIFY levelChanged)
    Q_PROPERTY(int levelDays READ levelDays NOTIFY levelDaysChanged)
    Q_PROPERTY(int levelHours READ levelHours NOTIFY levelHoursChanged)
    Q_PROPERTY(int levelRemainDays READ levelRemainDays NOTIFY levelRemainDaysChanged)

    Q_PROPERTY(QString birthday READ birthday NOTIFY birthdayChanged)
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

    explicit UQQMember(int category = 0, const QString &uin = "", QObject *parent = 0);
    
    QString uin() const;
    void setUin(QString uin);
    QString account() const;
    void setAccount(const QString &account);
    int category() const;
    void setCategory(int category);
    QString markname() const;
    void setMarkname(QString markname);
    QString nickname() const;
    void setNickname(const QString &nickname);
    QString longnick() const;
    void setLongnick(const QString &longnick);
    QUrl face() const;
    void setFace(const QUrl &face);
    bool isVip() const;
    void setVip(bool vip);
    int vipLevel() const;
    void setVipLevel(int vipLevel);
    int status() const;
    void setStatus(int status);
    int clientType() const;
    void setClientType(int clientType);

    // the member's detail
    int level() const;
    void setLevel(int level);
    int levelDays() const;
    void setLevelDays(int days);
    int levelHours() const;
    void setLevelHours(int hours);
    int levelRemainDays() const;
    void setLevelRemainDays(int remainDays);
    QString birthday() const;
    void setBirthday(const QString &birthday);
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

private:
    QString m_uin;
    QString m_account;
    int m_category;
    QString m_markname;
    QString m_nickname;
    QString m_longnick;
    int m_status;
    QUrl m_face;
    bool m_vip;
    int m_vipLevel;
    int m_clientType;
    /*
    {
    "retcode":0,
    "result":{
        "face":0,"birthday":{"month":3,"year":2013,"day":25},"occupation":"",
        "phone":"123456","allow":1,"college":"","uin":123456,"constel":1,"blood":1,
        "homepage":"","stat":0,"vip_info":0,"country":"","city":"","personal":"",
        "nick":"","shengxiao":1,"email":"","province":"","gender":"","mobile":""}
    }
    */
    int m_level;
    int m_levelDays;
    int m_levelHours;
    int m_levelRemainDays;
    QString m_birthday;
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


signals:
    void uinChanged();
    void accountChanged();
    void categoryChanged();
    void marknameChanged();
    void nicknameChanged();
    void longnickChanged();
    void statusChanged();
    void faceChanged();
    void vipChanged();
    void vipLevelChanged();

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

    void onlineChanged(bool online);

public slots:
    
};

#endif // UQQMEMBER_H
