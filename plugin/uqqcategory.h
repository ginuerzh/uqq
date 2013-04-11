#ifndef UQQCATEGORY_H
#define UQQCATEGORY_H

#include <QObject>
#include <QList>
#include "uqqmember.h"

class UQQCategory : public QObject
{
    Q_OBJECT
public:

    enum Category {
        BuddyCategory,
        //OnlineCategory = 0xF000,
        IllegalCategory = 0xFFFF
    };


    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int online READ online NOTIFY onlineChanged)
    Q_PROPERTY(int total READ total NOTIFY totalChanged)
    Q_PROPERTY(int catIndex READ catIndex NOTIFY catIndexChanged)

    explicit UQQCategory(QObject *parent = 0);
    
    QString name() const;
    void setName(const QString &name);
    int online() const;
    void setOnline(int online);
    int total() const;
    int catIndex() const;
    void setCatIndex(int index);

    //void setMembers(const QList<UQQMember *> &members);
    QList<QObject *> &members();
    void addMember(QObject *member);
    bool removeMember(UQQMember *member);
    bool removeMemberAt(int index);
    int hasMember(const QString &uin);
    void sort();

    void incOnline();
    void decOnline();
signals:
    void nameChanged();
    void onlineChanged();
    void totalChanged();
    void catIndexChanged();
    
public slots:

private:
    QString m_name;
    int m_online;
    int m_catIndex;

    QList<QObject *> m_members;
};

#endif // CATEGORY_H
