#include "uqqcategory.h"

UQQCategory::UQQCategory(QObject *parent) :
    QObject(parent)
{
    m_account = 0;
    m_online = 0;
    m_id = IllegalCategoryId;
    m_flag = 0;
    m_code = 0;
    m_groupInfo = Q_NULLPTR;
    m_groupReady = false;
    m_messageCount = 0;
    m_messageMask = MessageNotify;
}

quint64 UQQCategory::account() const {
    return m_account;
}
void UQQCategory::setAccount(quint64 account) {
    if (m_account != account) {
        m_account = account;
        emit accountChanged();
    }
}

QString UQQCategory::name() const {
    return m_name;
}
void UQQCategory::setName(const QString &name) {
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

QString UQQCategory::markname() const {
    return m_markname;
}
void UQQCategory::setMarkname(const QString &markname) {
    if (m_markname != markname) {
        m_markname = markname;
        emit marknameChanged();
    }
}

int UQQCategory::online() const {
    return m_online;
}
void UQQCategory::setOnline(int online) {
    if (online != m_online) {
        m_online = online;
        emit onlineChanged();
    }
}

int UQQCategory::total() const {
    return m_members.size();
}

quint64 UQQCategory::id() const {
    return m_id;
}
void UQQCategory::setId(quint64 id) {
    if (id != m_id) {
        m_id = id;
        emit idChanged();
    }
}

quint32 UQQCategory::flag() const {
    return m_flag;
}
void UQQCategory::setFlag(quint32 flag) {
    m_flag = flag;
}

quint64 UQQCategory::code() const {
    return m_code;
}
void UQQCategory::setCode(quint64 code) {
    m_code = code;
}

UQQGroupInfo *UQQCategory::groupInfo() const {
    return m_groupInfo;
}
void UQQCategory::setGroupInfo(UQQGroupInfo *groupInfo) {
    if (m_groupInfo != groupInfo) {
        m_groupInfo = groupInfo;
        emit groupInfoChanged();
    }
}

bool UQQCategory::groupReady() const {
    return m_groupReady;
}
void UQQCategory::setGroupReady(bool groupReady) {
    if (m_groupReady != groupReady) {
        m_groupReady = groupReady;
        emit groupReadyChanged();
    }
}

UQQCategory::GroupMessageMask UQQCategory::messageMask() const {
    return m_messageMask;
}
void UQQCategory::setMessageMask(GroupMessageMask messageMask) {
    if (m_messageMask != messageMask) {
        m_messageMask = messageMask;
        emit messageMaskChanged();
    }
}

QList<UQQMember *> UQQCategory::members() {
    return m_members.values();
}

UQQMember *UQQCategory::member(const QString &uin) {
    return m_members.value(uin);
}

bool sortLessThan(UQQMember *m1, UQQMember *m2) {
    if (m1->status() == UQQMember::OfflineStatus)
        return false;
    if (m2->status() == UQQMember::OfflineStatus)
        return true;

    return m1->status() < m2->status();
}

QList<UQQMember *> UQQCategory::sortedMembers() {
    QList<UQQMember *> members = m_members.values();
    qSort(members.begin(), members.end(), sortLessThan);
    return members;
}

void UQQCategory::addMember(UQQMember *member) {
    if (q_check_ptr(member)) {
        m_members.insert(member->uin(), member);
        emit totalChanged();
    }
}

int UQQCategory::removeMember(UQQMember *member) {
    if (!q_check_ptr(member)) return 0;

    int count = m_members.remove(member->uin());
    if (count > 0) {
        if (member->status() == UQQMember::OfflineStatus)
            decOnline();

        emit totalChanged();
    }
    return count;
}

bool UQQCategory::hasMember(const QString &uin) {
    return m_members.contains(uin);
}

void UQQCategory::incOnline() {
    setOnline(online() + 1);
}

void UQQCategory::decOnline() {
    if (online() > 0)
        setOnline(online() - 1);
}

void UQQCategory::addMessage(UQQMessage *message) {
    if (!q_check_ptr(message)) return;

    m_messages.append(message);
    setMessageCount(messageCount() + 1);
    emit messageReceived();
}

QList<QObject *> UQQCategory::messages(bool newMsg) {
    UQQMember *member;
    QList<QObject *> results;
    const QList<UQQMessage *> &messages =
            newMsg ? m_messages.mid(m_messages.count() - messageCount()) : m_messages;
    foreach (UQQMessage *message, messages) {
        member = this->member(message->src());
        if (q_check_ptr(member))
            message->setName(member->card() == "" ? member->nickname() : member->card());
        results.append(message);
    }
    setMessageCount(0);

    return results;
}

int UQQCategory::messageCount() const {
    return m_messageCount;
}

void UQQCategory::setMessageCount(int messageCount) {
    if (m_messageCount != messageCount) {
        m_messageCount = messageCount;
        emit messageCountChanged();
    }
}
