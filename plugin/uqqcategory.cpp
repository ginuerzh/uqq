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

QList<UQQMember *> UQQCategory::members() {
    return m_members.values();
}

UQQMember *UQQCategory::member(const QString &uin) {
    return m_members.value(uin);
}

bool sortLessThan(UQQMember *m1, UQQMember *m2) {
    return m1->status() < m2->status();
}

QList<UQQMember *> UQQCategory::sortedMembers() {
    QList<UQQMember *> members = m_members.values();
    qSort(members.begin(), members.end(), sortLessThan);
    return members;
}

void UQQCategory::addMember(UQQMember *member) {
    Q_CHECK_PTR(member);

    m_members.insert(member->uin(), member);
    emit totalChanged();

    UQQMember *m = qobject_cast<UQQMember *>(member);
    if (m->status() != UQQMember::OfflineStatus) {
        incOnline();
    }
}

int UQQCategory::removeMember(UQQMember *member) {
    Q_CHECK_PTR(member);
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
    Q_CHECK_PTR(message);
    m_messages.append(message);

    setMessageCount(messageCount() + 1);
    emit messageReceived();
}

QList<QObject *> UQQCategory::messages() {
    QList<QObject *> messages;
    UQQMessage *msg;
    UQQMember *member;
    foreach (msg, m_messages) {
        member = this->member(msg->src());
        Q_CHECK_PTR(member);
        if (member)
            msg->setName(member->markname() == "" ? member->nickname() : member->markname());
        messages.append(msg);
    }

    setMessageCount(0);
    return messages;
}

QList<QObject *> UQQCategory::newMessages() {
    QList<QObject *> newMsgs;
    UQQMessage *msg;
    UQQMember *member;

    if (messageCount() > 0) {
        QList<UQQMessage *> messages = m_messages.mid(m_messages.count() - messageCount());
        foreach (msg, messages) {
            member = this->member(msg->src());
            Q_CHECK_PTR(member);
            if (member)
                msg->setName(member->markname() == "" ? member->nickname() : member->markname());
            newMsgs.append(msg);
        }
    }
    setMessageCount(0);
    return newMsgs;
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
