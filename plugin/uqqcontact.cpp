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

    emit categoryReady();
}

void UQQContact::setMembers(const QVariantList &list) {
    QVariantMap m;
    UQQMember *member;
    int category;
    QString uin;

    //qDebug() << "total friends:" << list.size();
    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        category = m.value("categories").toInt() + 1;
        uin = m.value("uin").toString();
        member = new UQQMember(category, uin);
        m_members.insert(m.value("uin").toString(), member);

        addMemberToCategory(category, member);
    }
}

void UQQContact::setMarknames(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        m_members[m.value("uin").toString()]->setMarkname(m.value("markname").toString());
    }
}

void UQQContact::setVipInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("u").toString();
        m_members[uin]->setVip(m.value("is_vip").toBool());
        m_members[uin]->setVipLevel(m.value("vip_level").toInt());
    }
}

void UQQContact::setInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("uin").toString();
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
    UQQCategory *cate;
    if (category >= 0 && category < m_categories.size()) {
        cate = qobject_cast<UQQCategory *>(m_categories.at(category));
        cate->addMember(member);
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

void UQQContact::setOnlineBuddies(const QVariantList &list) {
    QVariantMap m;
    QString status;
    UQQMember *member;
    int online;
    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        status = m.value("status").toString();
        member = m_members[m.value("uin").toString()];
        member->setStatus(status);
        member->setClientType(m.value("client_type").toInt());

        online = categories().at(member->category())->online();
        categories().at(member->category())->setOnline(online + 1);
    }
}

QList<UQQMember *> &UQQContact::membersInCategory(int category) {
    return m_categories.at(category)->getMembers();
}

QString UQQContact::mapToJson(const QVariantMap &map) {
    QJsonDocument doc(QJsonObject::fromVariantMap(map));
    return doc.toJson();
}

QString UQQContact::listToJson(const QVariantList &list) {
    QJsonDocument doc(QJsonArray::fromVariantList(list));
    return doc.toJson();
}

