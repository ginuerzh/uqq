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
    qDebug() << "set group list...";
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
    qDebug() << "group list done, total group:" << list.size();
}

void UQQGroup::setGroupMarkList(const QVariantList &list) {
    QVariantMap m;
    UQQCategory *group = Q_NULLPTR;
    qDebug() << "set group markname list...";
    for (int i = 0; i < list.size(); i++) {
        m = list.at(i).toMap();
        group = getGroupById(m.value("uin").toULongLong());
        Q_CHECK_PTR(group);
        group->setMarkname(m.value("markname").toString());
    }
    qDebug() << "group markname list done, total markname list:" << list.size();
}

void UQQGroup::setGroupDetail(quint64 gid, const QVariantMap &map, UQQContact *contact) {
    UQQCategory *group = getGroupById(gid);
    Q_CHECK_PTR(group);
    if (!group) return;
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
    qDebug() << "set group info..." << group->id();
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
    qDebug() << "set group info done.";
}

void UQQGroup::setGroupMembers(UQQCategory *group, const QVariantList &members, UQQContact *contact) {
    QVariantMap m;
    QString uin;
    UQQMember *member;
    qDebug() << "set group members...";
    for (int i = 0; i < members.size(); i++) {
        m = members.at(i).toMap();
        uin = m.value("uin").toString();
        if ((member = contact->member(uin)) != Q_NULLPTR) {
            group->addMember(member);
            continue;
        }

        member = new UQQMember(group->id(), uin, this);
        member->setNickname(m.value("nick").toString());
        member->setIsFriend(false);
        group->addMember(member);
    }
    qDebug() << "set group members done, group members:" << members.size();
}

void UQQGroup::setMembersStats(UQQCategory *group, const QVariantList &stats) {
    QVariantMap m;
    UQQMember *member;
    qDebug() << "set group member stats..." << group->name();
    for (int i = 0; i < stats.size(); i++) {
        m = stats.at(i).toMap();
        member = group->member(m.value("uin").toString());
        Q_CHECK_PTR(member);
        if (member) {
            member->setClientType(m.value("client_type").toInt());
            member->setStatus(m.value("stat").toInt() / 10);
            //group->incOnline();   // the online info has some problem
            //qDebug() << "group member" << member->nickname() << "status:" << member->status();
        }
    }

    foreach(member, group->sortedMembers()) {
        if (member->status() != UQQMember::OfflineStatus) {
            group->incOnline();
        } else {
            break;
        }
    }

    qDebug() << "set group member stats done, online members:" << stats.size();
}

void UQQGroup::setMembersFlags(UQQCategory *group, const QVariantList &flags) {
    QVariantMap m;
    UQQMember *member;
    qDebug() << "set group member flags...";
    for (int i = 0; i < flags.size(); i++) {
        m = flags.at(i).toMap();
        member = group->member(m.value("muin").toString());
        Q_CHECK_PTR(member);
        if (member) {
            member->setFlag(m.value("mflag").toInt());
        }
    }
    qDebug() << "set group member flags done.";
}

void UQQGroup::setVipInfo(UQQCategory *group, const QVariantList &vips) {
    QVariantMap m;
    UQQMember *member;

    qDebug() << "set group member vip info...";
    for (int i = 0; i < vips.size(); i++) {
        m = vips.at(i).toMap();
        member = group->member(m.value("u").toString());
        Q_CHECK_PTR(member);
        if (member) {
            member->setVip(m.value("is_vip").toBool());
            member->setVipLevel(m.value("vip_level").toInt());
        }
    }
    qDebug() << "set group member vip info done.";
}

void UQQGroup::setMembersCards(UQQCategory *group, const QVariantList &cards) {
    QVariantMap m;
    UQQMember *member;
    qDebug() << "set group member cards...";
    for (int i = 0; i < cards.size(); i++) {
        m = cards.at(i).toMap();
        member = group->member(m.value("muin").toString());
        Q_CHECK_PTR(member);
        if (member) {
            //qDebug() << m.value("card").toString();
            member->setCard(m.value("card").toString());
        }
    }
    qDebug() << "set group member cards done.";
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

