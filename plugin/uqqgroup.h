#ifndef UQQGROUP_H
#define UQQGROUP_H

#include <QtQml>
#include "uqqcategory.h"
#include "uqqcontact.h"

class UQQGroup : public QObject
{
    Q_OBJECT
public:

    explicit UQQGroup(QObject *parent = 0);

    void setGroupData(const QVariantMap &map);
    void setGroupDetail(quint64 gid, const QVariantMap &map, UQQContact *contact);
    QList<UQQCategory *> &groups();
    UQQCategory *getGroupById(quint64 gid);
    UQQCategory *getGroupByCode(quint64 gcode);
    QList<UQQMember *> memberInGroup(quint64 gid, bool sorted);
    void setMemberDetail(quint64 gid, const QString &uin, const QVariantMap &m);
    
signals:
    
public slots:

private:
    void setGroupList(const QVariantList &list);
    void setGroupMarkList(const QVariantList &list);
    void setGroupInfo(UQQCategory *group, const QVariantMap &map);
    void setGroupMembers(UQQCategory *group, const QVariantList &members, UQQContact *contact);
    void setMembersStats(UQQCategory *group, const QVariantList &stats);
    void setMembersFlags(UQQCategory *group, const QVariantList &flags);
    void setMembersCards(UQQCategory *group, const QVariantList &cards);
    void setVipInfo(UQQCategory *group, const QVariantList &vips);
    
private:
    QList<UQQCategory *> m_groups;
};

#endif // UQQGROUP_H
