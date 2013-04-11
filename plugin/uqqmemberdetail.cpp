#include "uqqmemberdetail.h"

UQQMemberDetail::UQQMemberDetail(QObject *parent) :
    QObject(parent)
{
    setFaceid(0);
    setBlood(0);
    setShengxiao(0);
    setAllow(false);
    setConstel(0);
    setGender(Secret);
    setBirthday(QDateTime::currentDateTime());
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

QString UQQMemberDetail::nickname() const {
    return m_nickname;
}
void UQQMemberDetail::setNickname(const QString &nickname) {
    if (m_nickname != nickname) {
        m_nickname = nickname;
        emit nicknameChanged();
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
