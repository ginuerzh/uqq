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
        category = m.value("categories").toInt();
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
        UQQMember *member = this->member(uin);
        Q_CHECK_PTR(member);
        member->setMarkname(m.value("markname").toString());
    }
}

void UQQContact::setVipInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("u").toString();
        Q_ASSERT(uin.length() > 0);
        UQQMember *member = this->member(uin);
        Q_CHECK_PTR(member);
        member->setVip(m.value("is_vip").toBool());
        member->setVipLevel(m.value("vip_level").toInt());
    }
}

void UQQContact::setInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("uin").toString();
        Q_ASSERT(uin.length() > 0);
        UQQMember *member = this->member(uin);
        Q_CHECK_PTR(member);
        member->setNickname(m.value("nick").toString());
    }
}

void UQQContact::setCategories(const QVariantList &list) {
    QVariantMap m;
    UQQCategory *category;
/*
    category = new UQQCategory();
    category->setName("在线好友");
    category->setCatIndex(UQQCategory::OnlineCategory);
    m_categories.append(category);
*/
    category = new UQQCategory();
    category->setName("我的好友");
    category->setCatIndex(UQQCategory::BuddyCategory);
    m_categories.append(category);

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        category = new UQQCategory();
        category->setName(m.value("name").toString());
        category->setCatIndex(i + 1);
        m_categories.append(category);
    }
}

void UQQContact::addMemberToCategory(int category, UQQMember *member) {
    Q_CHECK_PTR(member);
    UQQCategory *cat = getCategory(category);
    if (cat) cat->addMember(member);
}

UQQCategory * UQQContact::getCategory(int cat) {
    for (int i = 0; i < m_categories.size(); i++) {
        if (m_categories.at(i)->catIndex() == cat) {
            return m_categories.at(i);
        }
    }

    return Q_NULLPTR;
}

QList<UQQCategory *> &UQQContact::categories() {
    return m_categories;
}

QHash<QString, UQQMember*> &UQQContact::members() {
    return m_members;
}

UQQMember *UQQContact::member(const QString &uin) {
    Q_ASSERT(uin.length() > 0);
    if (m_members.contains(uin))
        return m_members.value(uin);
    else
        return Q_NULLPTR;
}

void UQQContact::setOnlineBuddies(const QVariantList &list) {
    QVariantMap m;
    QString status;
    QString uin;
    UQQMember *member;

    //qDebug() << "online buddies:" << list.size();
    // the list may contain duplicate entry
    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        status = m.value("status").toString();
        uin = m.value("uin").toString();
        Q_ASSERT(uin.length() > 0);
        member = this->member(uin);
        member->setStatus(UQQMember::statusIndex(status));
        member->setClientType(m.value("client_type").toInt());
    }

    setCategoryMembers();
}

void UQQContact::setCategoryMembers() {
    UQQMember *member;
    //qDebug() << "setCategoryMembers";
    for (QHash<QString, UQQMember *>::const_iterator iter = m_members.begin();
         iter != m_members.end(); iter++) {
        member = iter.value();
        addMemberToCategory(member->category(), member);
/*
        if (member->status() != UQQMember::OfflineStatus &&
                member->category() != UQQCategory::IllegalCategory) {
            addMemberToCategory(UQQCategory::OnlineCategory, member);
        }
*/
    }

    for (int j = 0; j < m_categories.size(); j++) {
        m_categories.at(j)->sort();
    }
}

void UQQContact::setBuddyStatus(QString uin, int status, int clientType) {
    Q_ASSERT(uin.length() > 0);
    UQQMember *member = this->member(uin);
    Q_CHECK_PTR(member);
    //qDebug() << "old" << member->status() << member->clientType();
    int oldStatus = member->status();
    member->setStatus(status);
    member->setClientType(clientType);

    //qDebug() << member->category() << uin << status << clientType;
    if (oldStatus == status) return;

    //UQQCategory *onlineCat = getCategory(UQQCategory::OnlineCategory);
    UQQCategory *cat = getCategory(member->category());
    Q_CHECK_PTR(cat);

    if (oldStatus == UQQMember::OfflineStatus) {  // offline -> online
        cat->incOnline();
        //onlineCat->addMember(member);
    } else if (status == UQQMember::OfflineStatus){    // online -> offline
        cat->decOnline();
        //onlineCat->removeMember(member);
    } else {
    }
}

QList<QObject *> &UQQContact::membersInCategory(int category) {
    UQQCategory *c = getCategory(category);
    Q_CHECK_PTR(c);

    return c->members();
}
