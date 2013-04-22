#include "uqqmember.h"

UQQMember::UQQMember(quint64 gid, const QString &uin, QObject *parent) :
    QObject(parent), m_uin(uin), m_gid(gid)
{
    setIsFriend(true);
    setVip(false);
    setVipLevel(0);
    setClientType(0);
    setStatus(OfflineStatus);
    setMessageCount(0);
    setFlag(0);
    setInputNotify(false);
    setDetail(Q_NULLPTR);
}

QString UQQMember::uin() const {
    return m_uin;
}
void UQQMember::setUin(QString uin) {
    m_uin = uin;
}

quint64 UQQMember::gid() const {
    return m_gid;
}
void UQQMember::setGid(quint64 gid) {
    if (m_gid != gid) {
        m_gid = gid;
        emit gidChanged();
    }
}

bool UQQMember::isFriend() const {
    return m_isFriend;
}
void UQQMember::setIsFriend(bool isFriend) {
    if (m_isFriend != isFriend) {
        m_isFriend = isFriend;
        emit isFriendChanged();
    }
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

QString UQQMember::card() const {
    return m_card;
}
void UQQMember::setCard(QString card) {
    if (m_card != card) {
        m_card = card;
        emit cardChanged();
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
    if (m_clientType != clientType) {
        m_clientType = clientType;
        emit clientTypeChanged();
    }
}

int UQQMember::flag() const {
    return m_flag;
}
void UQQMember::setFlag(int flag) {
    m_flag = flag;
}

bool UQQMember::inputNotify() const {
    return m_inputNotify;
}
void UQQMember::setInputNotify(bool inputNotify) {
    if (m_inputNotify != inputNotify) {
        m_inputNotify = inputNotify;
        emit inputNotifyChanged();
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

QString UQQMember::groupSig() const {
    return m_groupSig;
}
void UQQMember::setGroupSig(const QString &groupSig) {
    if (m_groupSig != groupSig) {
        m_groupSig = groupSig;
        emit groupSigChanged();
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
    m_messages.append(message);
    setMessageCount(messageCount() + 1);
    emit messageReceived();
}

QList<QObject *> UQQMember::messages(bool newMsg) {
    QList<QObject *> results;
    const QList<UQQMessage *> &messages =
            newMsg ? m_messages.mid(m_messages.count() - messageCount()) : m_messages;

    foreach (UQQMessage *message, messages) {
        results.append(message);
    }
    setMessageCount(0);

    return results;
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
