#ifndef UQQCONTACT_H
#define UQQCONTACT_H

#include <QtQml>
#include "uqqcategory.h"
#include "uqqmember.h"

class UQQContact : public QObject
{
    Q_OBJECT
public:
    explicit UQQContact(QObject *parent = 0);
    ~UQQContact();

    static QString mapToJson(const QVariantMap &map);
    static QString listToJson(const QVariantList &list);

    void setDataMap(const QVariantMap &map);
    void setOnlineBuddies(const QVariantList &list);
    QList<UQQCategory *> &categories();
    QHash<QString, UQQMember*> &members();
    QList<UQQMember *> &membersInCategory(int category);

private:
    void setCategories(const QVariantList &list);
    void setMembers(const QVariantList &list);
    void setMarknames(const QVariantList &list);
    void setVipInfo(const QVariantList &list);
    void setInfo(const QVariantList &list);
    bool addMemberToCategory(int category, UQQMember *member);

signals:
    void categoryReady();

public slots:

private:
    QList<UQQCategory *> m_categories;
    QHash<QString, UQQMember*> m_members;
};

#endif // UQQCONTACT_H
