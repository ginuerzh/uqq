#ifndef UQQCATEGORY_H
#define UQQCATEGORY_H

#include <QObject>
#include <QList>
#include "uqqmember.h"
#include "uqqgroupinfo.h"

class UQQCategory : public QObject
{
    Q_OBJECT
    Q_ENUMS(GroupMessageMask)

public:

    enum CategoryId {
        BuddyCategoryId,
        StrangerCategoryId = 0xFFFFFFFE,
        IllegalCategoryId = 0xFFFFFFFF
    };

    enum GroupMessageMask {
        MessageNotify,
        MessageNotNotify,
        MessageBlocked
    };

    Q_PROPERTY(quint64 account READ account NOTIFY accountChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString markname READ markname NOTIFY marknameChanged)
    Q_PROPERTY(int online READ online NOTIFY onlineChanged)
    Q_PROPERTY(int total READ total NOTIFY totalChanged)
    Q_PROPERTY(quint64 id READ id NOTIFY idChanged)
    Q_PROPERTY(UQQGroupInfo *groupInfo READ groupInfo NOTIFY groupInfoChanged)
    Q_PROPERTY(int messageCount READ messageCount NOTIFY messageCountChanged)
    Q_PROPERTY(bool groupReady READ groupReady NOTIFY groupReadyChanged)
    Q_PROPERTY(GroupMessageMask messageMask READ messageMask NOTIFY messageMaskChanged)

    explicit UQQCategory(QObject *parent = 0);
    
    quint64 account() const;
    void setAccount(quint64 uin);
    QString name() const;
    void setName(const QString &name);
    QString markname() const;
    void setMarkname(const QString &markname);
    int online() const;
    void setOnline(int online);
    int total() const;
    quint64 id() const;
    void setId(quint64 id);
    quint32 flag() const;
    void setFlag(quint32 flag);
    quint64 code() const;
    void setCode(quint64 code);

    UQQGroupInfo *groupInfo() const;
    void setGroupInfo(UQQGroupInfo *groupInfo);

    bool groupReady() const;
    void setGroupReady(bool groupReady);

    GroupMessageMask messageMask() const;
    void setMessageMask(GroupMessageMask mask);

    //void setMembers(const QList<UQQMember *> &members);
    QList<UQQMember *> members();
    UQQMember *member(const QString &uin);
    QList<UQQMember *> sortedMembers();
    void addMember(UQQMember *member);
    int removeMember(UQQMember *member);
    bool hasMember(const QString &uin);

    void incOnline();
    void decOnline();

    int messageCount() const;
    void setMessageCount(int messageCount);

    void addMessage(UQQMessage *message);
    Q_INVOKABLE QList<QObject *> messages(bool newMsg = false);

signals:
    void accountChanged();
    void nameChanged();
    void marknameChanged();
    void onlineChanged();
    void totalChanged();
    void idChanged();
    void groupInfoChanged();

    void messageCountChanged();
    void messageReceived();
    void groupReadyChanged();
    void messageMaskChanged();

public slots:

private:
    quint64 m_account;
    quint64 m_id;
    QString m_name;
    QString m_markname;
    quint32 m_flag;
    quint64 m_code;
    int m_online;
    bool m_groupReady;

    GroupMessageMask m_messageMask;

    QHash<QString, UQQMember*> m_members;
    UQQGroupInfo *m_groupInfo;
    QList<UQQMessage *> m_messages;
    int m_messageCount;
};

#endif // CATEGORY_H
