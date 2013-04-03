#include "uqqmember.h"

UQQMember::UQQMember(int category, const QString &uin, QObject *parent) :
    QObject(parent), m_uin(uin), m_category(category)
{
    setAccount("0");
    setVip(false);
    setVipLevel(0);
    setBlood(0);
    setShengxiao(0);
    setAllow(false);
    setClientType(0);
    setConstel(0);
    setStatus(OfflineStatus);
    setGender(Secret);
}

QString UQQMember::uin() const {
    return m_uin;
}
void UQQMember::setUin(QString uin) {
    m_uin = uin;
}

QString UQQMember::account() const {
    return m_account;
}
void UQQMember::setAccount(const QString &account) {
    if (m_account != account) {
        m_account = account;
        emit accountChanged();
    }
}

int UQQMember::category() const {
    return m_category;
}
void UQQMember::setCategory(int category) {
    m_category = category;
}

QString UQQMember::markname() const {
    return m_markname;
}
void UQQMember::setMarkname(QString markname) {
    m_markname = markname;
}

QString UQQMember::nickname() const {
    return m_nickname;
}
void UQQMember::setNickname(const QString &nickname) {
    m_nickname = nickname;
}

QString UQQMember::longnick() const {
    return m_longnick;
}
void UQQMember::setLongnick(const QString &longnick) {
    if (m_longnick != longnick) {
        m_longnick = longnick;
        emit longnickChanged();
    }
}

int UQQMember::status() const {
    return m_status;
}
void UQQMember::setStatus(int status) {
    if (status != m_status) {
        m_status = status;
        emit statusChanged();
    }
}

QUrl UQQMember::face() const {
    return m_face;
}
void UQQMember::setFace(const QUrl &face) {
    if (m_face != face) {
        m_face = face;
        emit faceChanged();
    }
}

bool UQQMember::isVip() const {
    return m_vip;
}
void UQQMember::setVip(bool vip) {
    m_vip = vip;
}

int UQQMember::vipLevel() const {
    return m_vipLevel;
}
void UQQMember::setVipLevel(int vipLevel) {
    m_vipLevel = vipLevel;
}

int UQQMember::clientType() const {
    return m_clientType;
}
void UQQMember::setClientType(int clientType) {
    m_clientType = clientType;
}

int UQQMember::level() const {
    return m_level;
}
void UQQMember::setLevel(int level) {
    if (level != m_level) {
        m_level = level;
        emit levelChanged();
    }
}

int UQQMember::levelDays() const {
    return m_levelDays;
}
void UQQMember::setLevelDays(int days) {
    if (m_levelDays != days) {
        m_levelDays = days;
        emit levelDaysChanged();
    }
}

int UQQMember::levelHours() const {
    return m_levelHours;
}
void UQQMember::setLevelHours(int hours) {
    if (m_levelHours != hours) {
        m_levelHours = hours;
        emit levelHoursChanged();
    }
}

int UQQMember::levelRemainDays() const {
    return m_levelRemainDays;
}
void UQQMember::setLevelRemainDays(int remainDays) {
    if (m_levelRemainDays != remainDays) {
        m_levelRemainDays = remainDays;
        emit levelRemainDaysChanged();
    }
}

QString UQQMember::birthday() const {
    return m_birthday;
}
void UQQMember::setBirthday(const QString &birthday) {
    if (birthday != m_birthday) {
        m_birthday = birthday;
        emit birthdayChanged();
    }
}

QString UQQMember::occupation() const {
    return m_occupation;
}
void UQQMember::setOccupation(const QString &occupation) {
    if (m_occupation != occupation) {
        m_occupation = occupation;
        emit occupationChanged();
    }
}

QString UQQMember::phone() const {
    return m_phone;
}
void UQQMember::setPhone(const QString &phone) {
    if (m_phone != phone) {
        m_phone = phone;
        emit phoneChanged();
    }
}

QString UQQMember::mobile() const {
    return m_mobile;
}
void UQQMember::setMobile(const QString &mobile) {
    if (m_mobile != mobile) {
        m_mobile = mobile;
        emit mobileChanged();
    }
}

bool UQQMember::allow() const {
    return m_allow;
}
void UQQMember::setAllow(bool allow) {
    if (m_allow != allow) {
        m_allow = allow;
        emit allowChanged();
    }
}

QString UQQMember::college() const {
    return m_college;
}
void UQQMember::setCollege(const QString &college) {
    if (m_college != college) {
        m_college = college;
        emit collegeChanged();
    }
}

int UQQMember::shengxiao() const {
    return m_shengxiao;
}
void UQQMember::setShengxiao(int shengxiao) {
    if (m_shengxiao != shengxiao) {
        m_shengxiao = shengxiao;
        emit shengxiaoChanged();
    }
}

int UQQMember::constel() const {
    return m_constel;
}
void UQQMember::setConstel(int constel) {
    if (m_constel != constel) {
        m_constel = constel;
        emit constelChanged();
    }
}

int UQQMember::blood() const {
    return m_blood;
}
void UQQMember::setBlood(int blood) {
    if (m_blood != blood) {
        m_blood = blood;
        emit bloodChanged();
    }
}

QString UQQMember::homepage() const {
    return m_homepage;
}
void UQQMember::setHomepage(const QString &homepage) {
    if (m_homepage != homepage) {
        m_homepage = homepage;
        emit homepageChanged();
    }
}

QString UQQMember::country() const {
    return m_country;
}
void UQQMember::setCountry(const QString &country) {
    if (m_country != country) {
        m_country = country;
        emit countryChanged();
    }
}

QString UQQMember::province() const {
    return m_province;
}
void UQQMember::setProvince(const QString &province) {
    if (m_province != province) {
        m_province = province;
        emit provinceChanged();
    }
}

QString UQQMember::city() const {
    return m_city;
}
void UQQMember::setCity(const QString &city) {
    if (m_city != city) {
        m_city = city;
        emit cityChanged();
    }
}

QString UQQMember::personal() const {
    return m_personal;
}
void UQQMember::setPersonal(const QString &personal) {
    if (m_personal != personal) {
        m_personal = personal;
        emit personalChanged();
    }
}

QString UQQMember::email() const {
    return m_email;
}
void UQQMember::setEmail(const QString &email) {
    if (m_email != email) {
        m_email = email;
        emit emailChanged();
    }
}

int UQQMember::gender() const {
    return m_gender;
}
void UQQMember::setGender(int gender) {
    if (m_gender != gender) {
        m_gender = gender;
        emit genderChanged();
    }
}

UQQMember::Status UQQMember::statusIndex(const QString &s) {
    Status si = OfflineStatus;

    if (s == "online") {
        si = OnlineStatus;
    } else if (s == "callme") {
        si = CallmeStatus;
    } else if (s == "busy") {
        si = BusyStatus;
    } else if (s == "away") {
        si = AwayStatus;
    } else if (s == "silent") {
        si = SilentStatus;
    } else if (s == "hidden") {
        si = HiddenStatus;
    } else {
        si = OfflineStatus;
    }
    return si;
}

UQQMember::Gender UQQMember::genderIndex(const QString &s) {
    Gender gender = Secret;
    if (s == "male") {
        gender = Male;
    } else if (s == "female") {
        gender = Female;
    } else {
        gender = Secret;
    }
    return gender;
}
