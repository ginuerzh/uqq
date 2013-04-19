#include "uqqgroup.h"

UQQGroup::UQQGroup(QObject *parent) :
    QObject(parent)
{
}

void UQQGroup::setGroupData(const QVariantMap &map) {
    setGroupList(map.value("gnamelist").toList());
    setGroupMarkList(map.value("gmarklist").toList());
}

void UQQGroup::setGroupList(const QVariantList &list) {
    QVariantMap m;
    UQQCategory *group = Q_NULLPTR;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        group = new UQQCategory(this);
        group->setName(m.value("name").toString());
        group->setId(m.value("gid").toLongLong());
        group->setFlag(m.value("flag").toLongLong());
        group->setCode(m.value("code").toLongLong());
        //qDebug() << m.value("flag").toLongLong() << m.value("gid").toLongLong()
        //         << m.value("code").toLongLong() << m.value("name").toString();
        m_groups.append(group);
    }
}

void UQQGroup::setGroupMarkList(const QVariantList &list) {
    QVariantMap m;
    UQQCategory *group = Q_NULLPTR;

    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        group = getGroupById(m.value("uin").toULongLong());
        Q_CHECK_PTR(group);
        group->setMarkname(m.value("markname").toString());
    }
}

void UQQGroup::setGroupDetail(quint64 gid, const QVariantMap &map, UQQContact *contact) {
    UQQCategory *group = getGroupById(gid);
    Q_CHECK_PTR(group);
    QVariantMap m = map.value("ginfo").toMap();

    setGroupInfo(group, map);
    setGroupMembers(group, map.value("minfo").toList(), contact);
    setMembersFlags(group, m.value("members").toList());
    setMembersStats(group, map.value("stats").toList());
    setMembersCards(group, map.value("cards").toList());
    setVipInfo(group, map.value("vipinfo").toList());

    group->setGroupReady(true);
}

void UQQGroup::setGroupInfo(UQQCategory *group, const QVariantMap &map) {
    QVariantMap m = map.value("ginfo").toMap();
    UQQGroupInfo *groupInfo = new UQQGroupInfo(group);
    groupInfo->setFaceid(m.value("face").toInt());
    groupInfo->setMemo(m.value("memo").toString());
    groupInfo->setFingerMemo(m.value("fingermemo").toString());
    groupInfo->setGclass(m.value("class").toString());
    QDateTime createTime = QDateTime::fromMSecsSinceEpoch(m.value("createtime").toLongLong() * 1000);
    groupInfo->setCreateTime(createTime);
    groupInfo->setFlag(m.value("flag").toInt());
    groupInfo->setLevel(m.value("level").toInt());
    groupInfo->setOwner(m.value("owner").toString());
    group->setGroupInfo(groupInfo);

}

void UQQGroup::setGroupMembers(UQQCategory *group, const QVariantList &members, UQQContact *contact) {
    QVariantMap m;
    QString uin;
    UQQMember *member;
    //UQQMemberDetail *detail;
    //qDebug() << "set group members" << group->id();
    for (int i = 0; i < members.size(); i++) {
        m = members.at(i).toMap();
        uin = m.value("uin").toString();
        if ((member = contact->member(uin)) != Q_NULLPTR) {
            qDebug() << "set group member:" << uin << "in contact";
            group->addMember(member);
            continue;
        }

        member = new UQQMember(group->id(), uin, this);
        member->setNickname(m.value("nick").toString());
        member->setIsFriend(false);
        /*  // this is not needed
        detail = new UQQMemberDetail(member);
        detail->setGender(UQQMemberDetail::genderIndex(m.value("gender").toString()));
        detail->setCountry(m.value("country").toString());
        detail->setProvince(m.value("province").toString());
        detail->setCity(m.value("city").toString());
        member->setDetail(detail);
        */
        group->addMember(member);
    }
    //qDebug() << "group members:" << members.size();
}

void UQQGroup::setMembersStats(UQQCategory *group, const QVariantList &stats) {
    QVariantMap m;
    UQQMember *member;

    for (int i = 0; i < stats.size(); i++) {
        m = stats.at(i).toMap();
        member = group->member(m.value("uin").toString());
        Q_CHECK_PTR(member);
        if (member) {
            member->setClientType(m.value("client_type").toInt());
            member->setStatus(m.value("stat").toInt() / 10);
            group->incOnline();
        }
    }
}

void UQQGroup::setMembersFlags(UQQCategory *group, const QVariantList &flags) {
    QVariantMap m;
    UQQMember *member;

    for (int i = 0; i < flags.size(); i++) {
        m = flags.at(i).toMap();
        member = group->member(m.value("muin").toString());
        Q_CHECK_PTR(member);
        if (member) {
            member->setFlag(m.value("mflag").toInt());
        }
    }
}

void UQQGroup::setVipInfo(UQQCategory *group, const QVariantList &vips) {
    QVariantMap m;
    UQQMember *member;

    for (int i = 0; i < vips.size(); i++) {
        m = vips.at(i).toMap();
        member = group->member(m.value("u").toString());
        Q_CHECK_PTR(member);
        if (member) {
            member->setVip(m.value("is_vip").toBool());
            member->setVipLevel(m.value("vip_level").toInt());
        }
    }
}

void UQQGroup::setMembersCards(UQQCategory *group, const QVariantList &cards) {
    QVariantMap m;
    UQQMember *member;

    for (int i = 0; i < cards.size(); i++) {
        m = cards.at(i).toMap();
        member = group->member(m.value("muin").toString());
        Q_CHECK_PTR(member);
        if (member) {
            //qDebug() << m.value("card").toString();
            member->setCard(m.value("card").toString());
        }
    }
}

void UQQGroup::setMemberDetail(quint64 gid, const QString &uin, const QVariantMap &m) {
    UQQMemberDetail *detail = Q_NULLPTR;

    UQQCategory *group = getGroupById(gid);
    Q_CHECK_PTR(group);
    UQQMember *member = group->member(uin);
    Q_CHECK_PTR(member);
    if ((detail = member->detail()) == Q_NULLPTR)
        detail = new UQQMemberDetail(member);

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
    member->setNickname(m.value("nick").toString());    // nickname not in detail
    detail->setShengxiao(m.value("shengxiao").toInt());
    detail->setEmail(m.value("email").toString());
    detail->setProvince(m.value("province").toString());
    detail->setGender(UQQMemberDetail::genderIndex(m.value("gender").toString()));
    detail->setMobile(m.value("mobile").toString());
    detail->setToken(m.value("token").toString());

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


QList<UQQCategory *> &UQQGroup::groups() {
     return m_groups;
}

UQQCategory *UQQGroup::getGroupById(quint64 gid) {
    for (int i = 0; i < m_groups.size(); i++) {
        if (m_groups.at(i)->id() == gid) {
            return m_groups.at(i);
        }
    }

    qDebug() << "group id" << gid << "not found!";
    return Q_NULLPTR;
}

UQQCategory *UQQGroup::getGroupByCode(quint64 gcode) {
    for (int i = 0; i < m_groups.size(); i++) {
        if (m_groups.at(i)->code() == gcode) {
            return m_groups.at(i);
        }
    }

    qDebug() << "group code" << gcode << "not found!";
    return Q_NULLPTR;
}

QList<UQQMember *> UQQGroup::memberInGroup(quint64 gid, bool sorted) {
    UQQCategory *grp = getGroupById(gid);
    Q_CHECK_PTR(grp);
    if (sorted)
        return grp->sortedMembers();
    else
        return grp->members();
}

