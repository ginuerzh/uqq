#include "uqqcategory.h"

UQQCategory::UQQCategory(QObject *parent) :
    QObject(parent), m_online(0), m_index(0)
{
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

int UQQCategory::index() const {
    return m_index;
}
void UQQCategory::setIndex(int index) {
    if (index != m_index) {
        m_index = index;
        emit indexChanged();
    }
}
/*
void UQQCategory::setMembers(const QList<UQQMember *> &members) {
    m_members = members;
}
*/
QList<QObject *> &UQQCategory::members() {
    return m_members;
}

void UQQCategory::addMember(QObject *member) {
    Q_CHECK_PTR(member);

    m_members.append(member);
    emit totalChanged();

    UQQMember *m = qobject_cast<UQQMember *>(member);
    if (m->status() != UQQMember::OfflineStatus) {
        incOnline();
    }
}

bool UQQCategory::removeMember(const QString &uin) {
    UQQMember *member;
    for (int i = 0; i < m_members.size(); i++) {
        member = qobject_cast<UQQMember *>(m_members.at(i));
        if (uin == member->uin()) {
           return removeMemberAt(i);
        }
    }
    return false;
}

bool UQQCategory::removeMemberAt(int index) {
    if (index >= 0 && index < m_members.size()) {

        UQQMember *m = qobject_cast<UQQMember *>(m_members.at(index));
        if (m->status() == UQQMember::OfflineStatus) {
            decOnline();
        }

        m_members.removeAt(index);
        emit totalChanged();

        return true;
    }
    return false;
}

int UQQCategory::hasMember(const QString &uin) {
    UQQMember *member;
    for (int i = 0; i < m_members.size(); i++) {
        member = qobject_cast<UQQMember *>(m_members.at(i));
        if (uin == member->uin()) {
            return i;
        }
    }
    return -1;
}

void UQQCategory::incOnline() {
    setOnline(online() + 1);
}

void UQQCategory::decOnline() {
    if (online() > 0)
        setOnline(online() - 1);
}

bool categoryLessThan(QObject *o1, QObject *o2) {
    UQQMember *m1 = qobject_cast<UQQMember *>(o1);
    UQQMember *m2 = qobject_cast<UQQMember *>(o2);
    return m1->status() < m2->status();
}

void UQQCategory::sort() {
    if (m_members.size() > 0)
        qSort(m_members.begin(), m_members.end(), categoryLessThan);
}
