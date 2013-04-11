#include "uqqmember.h"

UQQMember::UQQMember(int category, const QString &uin, QObject *parent) :
    QObject(parent), m_uin(uin), m_category(category)
{
    setDetail(Q_NULLPTR);
    setAccount("0");
    setVip(false);
    setVipLevel(0);
    setClientType(0);
    setStatus(OfflineStatus);
    setMessageCount(0);
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
    if (m_markname != markname) {
        m_markname = markname;
        emit marknameChanged();
    }
}

QString UQQMember::nickname() const {
    return m_nickname;
}
void UQQMember::setNickname(const QString &nickname) {
    if (m_nickname != nickname) {
        m_nickname = nickname;
        emit nicknameChanged();
    }
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

UQQMemberDetail *UQQMember::detail() const {
    return m_detail;
}
void UQQMember::setDetail(UQQMemberDetail *detail) {
    if (detail != m_detail) {
        m_detail = detail;
        emit detailChanged();
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

void UQQMember::addMessage(UQQMessage *message) {
    message->setName(markname() == "" ? nickname() : markname());
    m_messages.append(message);

    setMessageCount(messageCount() + 1);
    emit messageReceived();
}

QList<QObject *> UQQMember::messages() {
    QList<QObject *> messages;
    for (int i = 0; i < m_messages.size(); i++)
        messages.append(m_messages.at(i));

    setMessageCount(0);
    return messages;
}

QList<QObject *> UQQMember::newMessages() {
    QList<QObject *> newMsgs;
    if (messageCount() > 0) {
        QList<UQQMessage *> messages = m_messages.mid(m_messages.count() - messageCount());
        for (int i = 0; i < messages.count(); i++) {
            newMsgs.append(messages.at(i));
        }
    }
    setMessageCount(0);
    return newMsgs;
}

int UQQMember::messageCount() const {
    return m_messageCount;
}

void UQQMember::setMessageCount(int messageCount) {
    if (m_messageCount != messageCount) {
        m_messageCount = messageCount;
        emit messageCountChanged();
    }
}
