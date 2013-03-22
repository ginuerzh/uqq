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

    setFriends(map.value("friends").toList());
    setMarknames(map.value("marknames").toList());
    setVipInfo(map.value("vipinfo").toList());
    setInfo(map.value("info").toList());
    setCategories(map.value("categories").toList());
    setCategoryFriends();
}

void UQQContact::setFriends(const QVariantList &list) {
    QVariantMap m;
    qDebug() << "total friends:" << list.size();
    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        m.insert("status", "offline");  // default status is 'offline'
        m_friends.insert(m.value("uin").toString(), m); // key: 'uin', value: map
    }
}

void UQQContact::setMarknames(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        addFriendInfo(m.value("uin").toString(), "markname", m.value("markname"));
    }
}

void UQQContact::setVipInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("u").toString();
        addFriendInfo(uin, "vip_level", m.value("vip_level"));
        addFriendInfo(uin, "is_vip", m.value("is_vip"));
    }
}

void UQQContact::setInfo(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("uin").toString();
        addFriendInfo(uin, "face", m.value("face"));
        addFriendInfo(uin, "nick", m.value("nick"));
    }
}

void UQQContact::setCategories(const QVariantList &list) {
    QVariantMap m;

//    // 固定为'在线好友', 放在第一组
//    m.insert("sort", 0);
//    m.insert("name", "在线好友");
//    m_categories.append(m);

    m.insert("index", 0);
    m.insert("sort", 0);
    m.insert("name", "我的好友");
    m_categories.append(m);

    m_categories.append(list);

    for (int i = 0; i < m_categories.size(); i++) {
        m = m_categories.takeAt(i).toMap();
        m.insert("online", 0);  // online friends
        m.insert("total", 0);   // total friends
        m_categories.insert(i, m);
    }
}

void UQQContact::setCategoryFriends() {
    for (int i = 0; i < m_categories.size(); i++) {
        m_catefriends.append(friendsInCategory(i));
        addCategoryInfo(i, "total", m_catefriends.at(i).size());
    }
}

void UQQContact::setOnlineBuddies(const QVariantList &list) {
    QVariantMap m;

    //qDebug() << "status size:" << list.size();
    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        QString uin = m.value("uin").toString();
        addFriendInfo(uin, "status", m.value("status"));
        addFriendInfo(uin, "client_type", m.value("client_type"));

        int index = category(uin);
        if (index >= 0) {
            addCategoryInfo(index, "online", getCategoryInfo(index, "online").toInt() + 1);
        }
        m_onlines.append(m);
    }
    emit categoryReady(listToJson(m_categories));
}

QVariantList UQQContact::friendsInCategory(int index) {
    QVariantList list;
    if (index < 0 || index >= m_categories.size())
        return list;

    for (QHash<QString, QVariantMap>::const_iterator iter = m_friends.constBegin();
         iter != m_friends.constEnd(); iter++) {
        if (category(iter.key()) == index) {
            list << iter.value();
        }
    }
    return list;
}

QVariantList UQQContact::getCategoryFriends(int index) {
    QVariantList list;
    if (index < 0 || index >= m_catefriends.size())
        return list;
    return m_catefriends.at(index);
}

int UQQContact::category(const QString uin) {
    if (m_friends.empty() || !m_friends.contains(uin))
        return -1;
    return m_friends[uin].value("categories", -1).toInt();
}

bool UQQContact::addFriendInfo(const QString &uin,
                               const QString &key, const QVariant &value) {
    if (m_friends.empty() || !m_friends.contains(uin)) {
        qWarning() << "addFriendInfo error!" << uin << key << value.toString();
        return false;
    }

    m_friends[uin].insert(key, value);
    return true;
}

bool UQQContact::addCategoryInfo(int index,
                                 const QString &key, const QVariant &value) {
    if (index < 0 || index >= m_categories.size()) {
        qWarning() << "addCategoryInfo error!" << index << key << value.toString();
        return false;
    }

    QVariantMap m = m_categories.takeAt(index).toMap();
    m.insert(key, value);
    m_categories.insert(index, m);
    return true;
}

QVariant UQQContact::getCategoryInfo(int index, const QString &key) {
    if (index < 0 || index >= m_categories.size()) {
        qWarning() << "getCategoryInfo error!";
        return false;
    }
    return m_categories.at(index).toMap().value(key, "");
}


QString UQQContact::mapToJson(const QVariantMap &map) {
    QJsonDocument doc(QJsonObject::fromVariantMap(map));
    return doc.toJson();
}

QString UQQContact::listToJson(const QVariantList &list) {
    QJsonDocument doc(QJsonArray::fromVariantList(list));
    return doc.toJson();
}

