#ifndef UQQMEMBER_H
#define UQQMEMBER_H

#include <QObject>
#include <QUrl>
#include "uqqmessage.h"
#include "uqqmemberdetail.h"

class UQQMember : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_ENUMS(ClientType)
public:

    enum Status {
        NullStatus,
        OnlineStatus,
        OfflineStatus,
        AwayStatus,
        HiddenStatus,
        BusyStatus,
        CallmeStatus,
        SilentStatus
    };

    enum ClientType {
        DesktopClient = 1,
        MobileClient = 21,
        IphoneClient = 24,
        WebClient = 41
    };

    static Status statusIndex(const QString &s);

    Q_PROPERTY(QString uin READ uin NOTIFY uinChanged)
    Q_PROPERTY(quint64 gid READ gid NOTIFY gidChanged)
    Q_PROPERTY(bool isFriend READ isFriend NOTIFY isFriendChanged)
    Q_PROPERTY(QString markname READ markname NOTIFY marknameChanged)
    Q_PROPERTY(QString nickname READ nickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString card READ card NOTIFY cardChanged)
    Q_PROPERTY(QString longnick READ longnick NOTIFY longnickChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QUrl face READ face NOTIFY faceChanged)
    Q_PROPERTY(bool isVip READ isVip NOTIFY vipChanged)
    Q_PROPERTY(int vipLevel READ vipLevel NOTIFY vipLevelChanged)
    Q_PROPERTY(int clientType READ clientType NOTIFY clientTypeChanged)
    Q_PROPERTY(bool inputNotify READ inputNotify NOTIFY inputNotifyChanged)
    Q_PROPERTY(QString groupSig READ groupSig NOTIFY groupSigChanged)

    Q_PROPERTY(int messageCount READ messageCount NOTIFY messageCountChanged)

    Q_PROPERTY(UQQMemberDetail *detail READ detail NOTIFY detailChanged)

    explicit UQQMember(quint64 gid = 0, const QString &uin = "", QObject *parent = 0);
    
    QString uin() const;
    void setUin(QString uin);
    quint64 gid() const;
    void setGid(quint64 gid);
    bool isFriend() const;
    void setIsFriend(bool isFriend);
    QString markname() const;
    void setMarkname(QString markname);
    QString nickname() const;
    void setNickname(const QString &nickname);
    QString card() const;
    void setCard(QString card);
    QString longnick() const;
    void setLongnick(const QString &longnick);
    QUrl face() const;
    void setFace(const QUrl &face);
    bool isVip() const;
    void setVip(bool vip);
    int vipLevel() const;
    void setVipLevel(int vipLevel);
    int status() const;
    void setStatus(int status);
    int clientType() const;
    void setClientType(int clientType);
    int flag() const;
    void setFlag(int flag);
    bool inputNotify() const;
    void setInputNotify(bool inputNotify);

    QString groupSig() const;
    void setGroupSig(const QString &groupSig);

    UQQMemberDetail *detail() const;
    void setDetail(UQQMemberDetail *detail);

    int messageCount() const;
    void setMessageCount(int messageCount);

    void addMessage(UQQMessage *message);
    Q_INVOKABLE QList<QObject *> messages();
    Q_INVOKABLE QList<QObject *> newMessages();

private:
    QString m_uin;
    quint64 m_gid;
    bool m_isFriend;
    QString m_card;
    QString m_markname;
    QString m_nickname;
    QString m_longnick;
    int m_status;
    QUrl m_face;
    bool m_vip;
    int m_vipLevel;
    int m_clientType;
    int m_flag;
    bool m_inputNotify;

    QString m_groupSig;

    UQQMemberDetail *m_detail;

    QList<UQQMessage *> m_messages;
    int m_messageCount;

signals:
    void isFriendChanged();
    void uinChanged();
    void gidChanged();
    void marknameChanged();
    void nicknameChanged();
    void cardChanged();
    void longnickChanged();
    void statusChanged();
    void faceChanged();
    void vipChanged();
    void vipLevelChanged();
    void clientTypeChanged();
    void inputNotifyChanged();
    void groupSigChanged();

    void detailChanged();

    void messageCountChanged();
    void messageReceived();

public slots:
    
};

#endif // UQQMEMBER_H
