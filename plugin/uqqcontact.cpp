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
void UQQContact::setContactData(const QVariantMap &map) {

    setCategories(map.value("categories").toList());

    setMembers(map.value("friends").toList());
    setMarknames(map.value("marknames").toList());
    setVipInfo(map.value("vipinfo").toList());
    setNickname(map.value("info").toList());
}

void UQQContact::addMember(UQQMember *member) {
    if (member) {
        Q_ASSERT(member->uin().length() > 0);
        m_members.insert(member->uin(), member);
    }
}

void UQQContact::setMembers(const QVariantList &list) {
    QVariantMap m;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        addMember(new UQQMember(m.value("categories").toInt(), m.value("uin").toString(), this));
    }
}

void UQQContact::setMarknames(const QVariantList &list) {
    QVariantMap m;
    UQQMember *member;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        member = this->member(m.value("uin").toString());
        Q_CHECK_PTR(member);
        if (member)
            member->setMarkname(m.value("markname").toString());
    }
}

void UQQContact::setVipInfo(const QVariantList &list) {
    QVariantMap m;
    UQQMember *member;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        member = this->member(m.value("u").toString());
        Q_CHECK_PTR(member);
        if (member) {
            member->setVip(m.value("is_vip").toBool());
            member->setVipLevel(m.value("vip_level").toInt());
        }
    }
}

void UQQContact::setNickname(const QVariantList &list) {
    QVariantMap m;
    UQQMember *member;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        member = this->member(m.value("uin").toString());
        Q_CHECK_PTR(member);
        if (member)
            member->setNickname(m.value("nick").toString());
    }
}

void UQQContact::setMemberDetail(const QString &uin, const QVariantMap &m) {
    UQQMember *member = this->member(uin);
    Q_CHECK_PTR(member);

    UQQMemberDetail *detail = new UQQMemberDetail(member);
    detail->setFaceid(m.value("face").toInt());
    detail->setOccupation(m.value("occupation").toString());
    detail->setPhone(m.value("phone").toString());
    detail->setAllow(m.value("allow").toBool());
    detail->setCollege(m.value("college").toString());
    detail->setConstel(m.value("constel").toInt());
    detail->setBlood(m.value("blood").toInt());
    detail->setHomepage(m.value("homepage").toString());
    detail->setCountry(m.value("country").toString());
    detail->setCity(m.value("city").toString());
    detail->setPersonal(m.value("personal").toString());
    detail->setNickname(m.value("nick").toString());
    detail->setShengxiao(m.value("shengxiao").toInt());
    detail->setEmail(m.value("email").toString());
    detail->setProvince(m.value("province").toString());
    detail->setGender(UQQMemberDetail::genderIndex(m.value("gender").toString()));
    detail->setMobile(m.value("mobile").toString());

    QVariantMap birth = m.value("birthday").toMap();
    int year = birth.value("year").toInt();
    int month = birth.value("month").toInt();
    int day = birth.value("day").toInt();
    if (QDate::isValid(year, month, day)) {
        QDateTime birth;
        birth.setDate(QDate(year, month, day));
        detail->setBirthday(birth);
    }

    member->setDetail(detail);
}

void UQQContact::setCategories(const QVariantList &list) {
    QVariantMap m;
    UQQCategory *category = Q_NULLPTR;
/*
    category = new UQQCategory();
    category->setName("在线好友");
    category->setId(UQQCategory::OnlineCategoryId);
    m_categories.append(category);
*/
    category = new UQQCategory(this);
    category->setName("我的好友");
    category->setId(UQQCategory::BuddyCategoryId);
    m_categories.append(category);

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        category = new UQQCategory(this);
        category->setName(m.value("name").toString());
        category->setId(i + 1);
        m_categories.append(category);
    }
}

void UQQContact::addMemberToCategory(int category, UQQMember *member) {
    Q_CHECK_PTR(member);
    UQQCategory *cat = getCategory(category);
    if (cat) cat->addMember(member);
}

UQQCategory * UQQContact::getCategory(quint64 gid) {
    for (int i = 0; i < m_categories.size(); i++) {
        if (m_categories.at(i)->id() == gid) {
            return m_categories.at(i);
        }
    }
    qDebug() << "catetory" << gid << "not found!";
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
        addMemberToCategory(member->gid(), member);
/*
        if (member->status() != UQQMember::OfflineStatus &&
                member->category() != UQQCategory::IllegalCategory) {
            addMemberToCategory(UQQCategory::OnlineCategory, member);
        }
*/
    }
}

void UQQContact::setBuddyStatus(QString uin, int status, int clientType) {
    Q_ASSERT(uin.length() > 0);
    UQQMember *member = this->member(uin);
    Q_CHECK_PTR(member);

    int oldStatus = member->status();
    member->setStatus(status);
    member->setClientType(clientType);

    if (oldStatus == status) return;

    UQQCategory *cat = getCategory(member->gid());
    Q_CHECK_PTR(cat);

    if (oldStatus == UQQMember::OfflineStatus) {  // offline -> online
        cat->incOnline();
    } else if (status == UQQMember::OfflineStatus){    // online -> offline
        cat->decOnline();
    } else {
    }
}

QList<UQQMember *> UQQContact::membersInCategory(quint64 catid, bool sorted) {
    UQQCategory *c = getCategory(catid);
    Q_CHECK_PTR(c);
    if (sorted)
        return c->sortedMembers();
    else
        return c->members();
}
