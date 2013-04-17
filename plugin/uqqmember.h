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
    Q_PROPERTY(QString account READ account NOTIFY accountChanged)
    Q_PROPERTY(quint64 gid READ gid NOTIFY gidChanged)
    Q_PROPERTY(QString markname READ markname NOTIFY marknameChanged)
    Q_PROPERTY(QString nickname READ nickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString longnick READ longnick NOTIFY longnickChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QUrl face READ face NOTIFY faceChanged)
    Q_PROPERTY(bool isVip READ isVip NOTIFY vipChanged)
    Q_PROPERTY(int vipLevel READ vipLevel NOTIFY vipLevelChanged)
    Q_PROPERTY(int clientType READ clientType NOTIFY clientTypeChanged)
    Q_PROPERTY(bool inputNotify READ inputNotify NOTIFY inputNotifyChanged)
    Q_PROPERTY(QString groupSig READ groupSig NOTIFY groupSigChanged)

    Q_PROPERTY(int level READ level NOTIFY levelChanged)
    Q_PROPERTY(int levelDays READ levelDays NOTIFY levelDaysChanged)
    Q_PROPERTY(int levelHours READ levelHours NOTIFY levelHoursChanged)
    Q_PROPERTY(int levelRemainDays READ levelRemainDays NOTIFY levelRemainDaysChanged)

    Q_PROPERTY(int messageCount READ messageCount NOTIFY messageCountChanged)

    Q_PROPERTY(UQQMemberDetail *detail READ detail NOTIFY detailChanged)

    explicit UQQMember(quint64 gid = 0, const QString &uin = "", QObject *parent = 0);
    
    QString uin() const;
    void setUin(QString uin);
    QString account() const;
    void setAccount(const QString &account);
    quint64 gid() const;
    void setGid(quint64 gid);
    QString markname() const;
    void setMarkname(QString markname);
    QString nickname() const;
    void setNickname(const QString &nickname);
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

    int level() const;
    void setLevel(int level);
    int levelDays() const;
    void setLevelDays(int days);
    int levelHours() const;
    void setLevelHours(int hours);
    int levelRemainDays() const;
    void setLevelRemainDays(int remainDays);

    UQQMemberDetail *detail() const;
    void setDetail(UQQMemberDetail *detail);

    int messageCount() const;
    void setMessageCount(int messageCount);

    void addMessage(UQQMessage *message);
    Q_INVOKABLE QList<QObject *> messages();
    Q_INVOKABLE QList<QObject *> newMessages();

private:
    QString m_uin;
    QString m_account;
    quint64 m_gid;
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

    int m_level;
    int m_levelDays;
    int m_levelHours;
    int m_levelRemainDays;

    UQQMemberDetail *m_detail;

    QList<UQQMessage *> m_messages;
    int m_messageCount;

signals:
    void uinChanged();
    void accountChanged();
    void gidChanged();
    void marknameChanged();
    void nicknameChanged();
    void longnickChanged();
    void statusChanged();
    void faceChanged();
    void vipChanged();
    void vipLevelChanged();
    void clientTypeChanged();
    void inputNotifyChanged();
    void groupSigChanged();

    void levelChanged();
    void levelDaysChanged();
    void levelHoursChanged();
    void levelRemainDaysChanged();

    void detailChanged();

    void messageCountChanged();
    void messageReceived();

public slots:
    
};

#endif // UQQMEMBER_H
