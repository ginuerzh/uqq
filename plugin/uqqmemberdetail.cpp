#include "uqqmemberdetail.h"

UQQMemberDetail::UQQMemberDetail(QObject *parent) :
    QObject(parent)
{
    setAccount(0);
    setLevel(0);
    setLevelDays(0);
    setLevelHours(0);
    setLevelRemainDays(0);
    setFaceid(0);
    setBlood(0);
    setShengxiao(0);
    setAllow(false);
    setConstel(0);
    setGender(Secret);
    setBirthday(QDateTime::currentDateTime());
}

quint64 UQQMemberDetail::account() const {
    return m_account;
}
void UQQMemberDetail::setAccount(quint64 account) {
    if (m_account != account) {
        m_account = account;
        emit accountChanged();
    }
}

int UQQMemberDetail::level() const {
    return m_level;
}
void UQQMemberDetail::setLevel(int level) {
    if (level != m_level) {
        m_level = level;
        emit levelChanged();
    }
}

int UQQMemberDetail::levelDays() const {
    return m_levelDays;
}
void UQQMemberDetail::setLevelDays(int days) {
    if (m_levelDays != days) {
        m_levelDays = days;
        emit levelDaysChanged();
    }
}

int UQQMemberDetail::levelHours() const {
    return m_levelHours;
}
void UQQMemberDetail::setLevelHours(int hours) {
    if (m_levelHours != hours) {
        m_levelHours = hours;
        emit levelHoursChanged();
    }
}

int UQQMemberDetail::levelRemainDays() const {
    return m_levelRemainDays;
}
void UQQMemberDetail::setLevelRemainDays(int remainDays) {
    if (m_levelRemainDays != remainDays) {
        m_levelRemainDays = remainDays;
        emit levelRemainDaysChanged();
    }
}

int UQQMemberDetail::faceid() const {
    return m_faceid;
}
void UQQMemberDetail::setFaceid(int faceid) {
    m_faceid = faceid;
}

QDateTime UQQMemberDetail::birthday() const {
    return m_birthday;
}
void UQQMemberDetail::setBirthday(const QDateTime &birthday) {
    if (birthday != m_birthday) {
        m_birthday = birthday;
        emit birthdayChanged();
    }
}

QString UQQMemberDetail::occupation() const {
    return m_occupation;
}
void UQQMemberDetail::setOccupation(const QString &occupation) {
    if (m_occupation != occupation) {
        m_occupation = occupation;
        emit occupationChanged();
    }
}

QString UQQMemberDetail::phone() const {
    return m_phone;
}
void UQQMemberDetail::setPhone(const QString &phone) {
    if (m_phone != phone) {
        m_phone = phone;
        emit phoneChanged();
    }
}

QString UQQMemberDetail::mobile() const {
    return m_mobile;
}
void UQQMemberDetail::setMobile(const QString &mobile) {
    if (m_mobile != mobile) {
        m_mobile = mobile;
        emit mobileChanged();
    }
}

bool UQQMemberDetail::allow() const {
    return m_allow;
}
void UQQMemberDetail::setAllow(bool allow) {
    if (m_allow != allow) {
        m_allow = allow;
        emit allowChanged();
    }
}

QString UQQMemberDetail::college() const {
    return m_college;
}
void UQQMemberDetail::setCollege(const QString &college) {
    if (m_college != college) {
        m_college = college;
        emit collegeChanged();
    }
}

int UQQMemberDetail::shengxiao() const {
    return m_shengxiao;
}
void UQQMemberDetail::setShengxiao(int shengxiao) {
    if (m_shengxiao != shengxiao) {
        m_shengxiao = shengxiao;
        emit shengxiaoChanged();
    }
}

int UQQMemberDetail::constel() const {
    return m_constel;
}
void UQQMemberDetail::setConstel(int constel) {
    if (m_constel != constel) {
        m_constel = constel;
        emit constelChanged();
    }
}

int UQQMemberDetail::blood() const {
    return m_blood;
}
void UQQMemberDetail::setBlood(int blood) {
    if (m_blood != blood) {
        m_blood = blood;
        emit bloodChanged();
    }
}

QString UQQMemberDetail::homepage() const {
    return m_homepage;
}
void UQQMemberDetail::setHomepage(const QString &homepage) {
    if (m_homepage != homepage) {
        m_homepage = homepage;
        emit homepageChanged();
    }
}

QString UQQMemberDetail::country() const {
    return m_country;
}
void UQQMemberDetail::setCountry(const QString &country) {
    if (m_country != country) {
        m_country = country;
        emit countryChanged();
    }
}

QString UQQMemberDetail::province() const {
    return m_province;
}
void UQQMemberDetail::setProvince(const QString &province) {
    if (m_province != province) {
        m_province = province;
        emit provinceChanged();
    }
}

QString UQQMemberDetail::city() const {
    return m_city;
}
void UQQMemberDetail::setCity(const QString &city) {
    if (m_city != city) {
        m_city = city;
        emit cityChanged();
    }
}

QString UQQMemberDetail::personal() const {
    return m_personal;
}
void UQQMemberDetail::setPersonal(const QString &personal) {
    if (m_personal != personal) {
        m_personal = personal;
        emit personalChanged();
    }
}

QString UQQMemberDetail::email() const {
    return m_email;
}
void UQQMemberDetail::setEmail(const QString &email) {
    if (m_email != email) {
        m_email = email;
        emit emailChanged();
    }
}

int UQQMemberDetail::gender() const {
    return m_gender;
}
void UQQMemberDetail::setGender(int gender) {
    if (m_gender != gender) {
        m_gender = gender;
        emit genderChanged();
    }
}

UQQMemberDetail::Gender UQQMemberDetail::genderIndex(const QString &s) {
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

QString UQQMemberDetail::token() const {
    return m_token;
}
void UQQMemberDetail::setToken(const QString &token) {
    if (m_token != token) {
        m_token = token;
        emit tokenChanged();
    }
}
