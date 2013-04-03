#include "uqqcontact.h"


UQQContact::UQQContact(QObject *parent) :
    QObject(parent)
{
}

UQQContact::~UQQContact() {
}

/*
 *       {
 *           "friends":[{"flag":0,"uin":123456,"categories":0},...,{...}],
 *           "marknames":[{"uin":123456,"markname":""},...,{...}],
 *           "categories":[{"index":1,"sort":4,"name":""},...,,{...}],
 *           "vipinfo":[{"vip_level":0,"u":1234567,"is_vip":0},...,{...}],
 *           "info":[{"face":0,"flag":0,"nick":"","uin":1234567},...,{...}]
 *       }
*/
void UQQContact::setDataMap(const QVariantMap &map) {

    setCategories(map.value("categories").toList());

    setMembers(map.value("friends").toList());
    setMarknames(map.value("marknames").toList());
    setVipInfo(map.value("vipinfo").toList());
    setInfo(map.value("info").toList());
}

void UQQContact::addMember(UQQMember *member) {
    if (member) {
        Q_ASSERT(member->uin().length() > 0);
        m_members.insert(member->uin(), member);
    }
}

void UQQContact::setMembers(const QVariantList &list) {
    QVariantMap m;
    int category;
    QString uin;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        category = m.value("categories").toInt() + 1;
        uin = m.value("uin").toString();
        addMember(new UQQMember(category, uin));
    }
}

void UQQContact::setMarknames(const QVariantList &list) {
    QVariantMap m;
    QString uin;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        uin = m.value("uin").toString();
        Q_ASSERT(uin.length() > 0);
        m_members[uin]->setMarkname(m.value("markname").toString());
    }
}

void UQQContact::setVipInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("u").toString();
        Q_ASSERT(uin.length() > 0);
        m_members[uin]->setVip(m.value("is_vip").toBool());
        m_members[uin]->setVipLevel(m.value("vip_level").toInt());
    }
}

void UQQContact::setInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("uin").toString();
        Q_ASSERT(uin.length() > 0);
        m_members[uin]->setNickname(m.value("nick").toString());
    }
}

void UQQContact::setCategories(const QVariantList &list) {
    QVariantMap m;
    UQQCategory *category;

    category = new UQQCategory();
    category->setName("在线好友");
    category->setIndex(0);
    m_categories.append(category);

    category = new UQQCategory();
    category->setName("我的好友");
    category->setIndex(1);
    m_categories.append(category);

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        category = new UQQCategory();
        category->setName(m.value("name").toString());
        category->setIndex(i + 2);
        m_categories.append(category);
    }

    //qDebug() << "setCategories:" << m_categories.size();
}

bool UQQContact::addMemberToCategory(int category, UQQMember *member) {
    Q_ASSERT(category >= 0 && category < m_categories.size());
    Q_CHECK_PTR(member);

    if (category >= 0 && category < m_categories.size()) {
        m_categories.at(category)->addMember(member);
        return true;
    }
    return false;
}

QList<UQQCategory *> &UQQContact::categories() {
    return m_categories;
}

QHash<QString, UQQMember*> &UQQContact::members() {
    return m_members;
}

UQQMember *UQQContact::member(const QString &uin) {
    Q_ASSERT(uin.length() > 0);
    return m_members[uin];
}

void UQQContact::setOnlineBuddies(const QVariantList &list) {
    QVariantMap m;
    QString status;
    QString uin;
    UQQMember *member;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        status = m.value("status").toString();
        uin = m.value("uin").toString();
        Q_ASSERT(uin.length() > 0);
        member = m_members[uin];
        member->setStatus(UQQMember::statusIndex(status));
        member->setClientType(m.value("client_type").toInt());
        addMemberToCategory(UQQCategory::OnlineCategory, member);
    }

    setCategoryMembers();
}

void UQQContact::setCategoryMembers() {
    UQQMember *member;
    for (QHash<QString, UQQMember *>::const_iterator iter = m_members.begin();
         iter != m_members.end(); iter++) {
        member = iter.value();
        addMemberToCategory(member->category(), member);
    }

    for (int j = 0; j < m_categories.size(); j++) {
        m_categories.at(j)->sort();
    }
}

void UQQContact::setBuddyStatus(QString uin, int status, int clientType) {
    Q_ASSERT(uin.length() > 0);
    UQQMember *member = m_members[uin];
    int old = member->status();
    member->setStatus(status);
    member->setClientType(clientType);

    int index = member->category();
    Q_ASSERT(index >= 0 && index < m_categories.size());
    m_categories.at(index)->sort();

    // qDebug() << "setBuddyStatus:" << uin << old << status << clientType;
    // remain online
    if (old == status || (old < UQQMember::OfflineStatus && status < UQQMember::OfflineStatus))
        return;

    UQQCategory *category = m_categories.at(UQQCategory::OnlineCategory);
    // offline -> online
    if (old == UQQMember::OfflineStatus) {
        m_categories.at(index)->incOnline();
        category->addMember(member);
    } else {    // online -> offline
        m_categories.at(index)->decOnline();
        category->removeMember(uin);
    }

    category->sort();
}

QList<QObject *> &UQQContact::membersInCategory(int category) {
    Q_ASSERT(category >= 0 && category < m_categories.size());
    return m_categories.at(category)->members();
}
/*
QString UQQContact::mapToJson(const QVariantMap &map) {
    QJsonDocument doc(QJsonObject::fromVariantMap(map));
    return doc.toJson();
}

QString UQQContact::listToJson(const QVariantList &list) {
    QJsonDocument doc(QJsonArray::fromVariantList(list));
    return doc.toJson();
}
*/
