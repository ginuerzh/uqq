#include "uqqmember.h"

UQQMember::UQQMember(int category, QString uin, QObject *parent) :
    QObject(parent), m_uin(uin), m_category(category)
{
    setAccount(0);
    setVip(false);
    setVipLevel(0);
}

QString UQQMember::uin() const {
    return m_uin;
}
void UQQMember::setUin(QString uin) {
    m_uin = uin;
}

int UQQMember::account() const {
    return m_account;
}
void UQQMember::setAccount(int account) {
    m_account = account;
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

QString UQQMember::status() const {
    return m_status;
}
void UQQMember::setStatus(const QString &status) {
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
