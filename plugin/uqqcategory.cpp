#include "uqqcategory.h"

UQQCategory::UQQCategory(QObject *parent) :
    QObject(parent), m_online(0), m_total(0), m_index(0)
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
    return m_total;
}
void UQQCategory::setTotal(int total) {
    if (total != m_total) {
        m_total = total;
        emit totalChanged();
    }
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

void UQQCategory::setMembers(const QList<UQQMember *> &members) {
    m_members = members;
}

QList<UQQMember *> &UQQCategory::getMembers() {
    return m_members;
}

void UQQCategory::addMember(UQQMember *member) {
    m_total++;
    m_members.append(member);
}
