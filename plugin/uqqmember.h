#ifndef UQQMEMBER_H
#define UQQMEMBER_H

#include <QObject>
#include <QUrl>
#include "uqqmessage.h"
#include "uqqmemberdetail.h"

class UQQMember : public QObject
{
    Q_OBJECT
public:

    enum Status {
        OnlineStatus,
        CallmeStatus,
        BusyStatus,
        AwayStatus,
        SilentStatus,
        HiddenStatus,
        OfflineStatus
    };

    static Status statusIndex(const QString &s);

    Q_PROPERTY(QString uin READ uin NOTIFY uinChanged)
    Q_PROPERTY(QString account READ account NOTIFY accountChanged)
    Q_PROPERTY(int category READ category NOTIFY categoryChanged)
    Q_PROPERTY(QString markname READ markname NOTIFY marknameChanged)
    Q_PROPERTY(QString nickname READ nickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString longnick READ longnick NOTIFY longnickChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QUrl face READ face NOTIFY faceChanged)
    Q_PROPERTY(bool isVip READ isVip NOTIFY vipChanged)
    Q_PROPERTY(int vipLevel READ vipLevel NOTIFY vipLevelChanged)

    Q_PROPERTY(int level READ level NOTIFY levelChanged)
    Q_PROPERTY(int levelDays READ levelDays NOTIFY levelDaysChanged)
    Q_PROPERTY(int levelHours READ levelHours NOTIFY levelHoursChanged)
    Q_PROPERTY(int levelRemainDays READ levelRemainDays NOTIFY levelRemainDaysChanged)

    Q_PROPERTY(int messageCount READ messageCount NOTIFY messageCountChanged)

    Q_PROPERTY(UQQMemberDetail *detail READ detail NOTIFY detailChanged)

    explicit UQQMember(int category = 0, const QString &uin = "", QObject *parent = 0);
    
    QString uin() const;
    void setUin(QString uin);
    QString account() const;
    void setAccount(const QString &account);
    int category() const;
    void setCategory(int category);
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
    int m_category;
    QString m_markname;
    QString m_nickname;
    QString m_longnick;
    int m_status;
    QUrl m_face;
    bool m_vip;
    int m_vipLevel;
    int m_clientType;
    int m_flag;

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
    void categoryChanged();
    void marknameChanged();
    void nicknameChanged();
    void longnickChanged();
    void statusChanged();
    void faceChanged();
    void vipChanged();
    void vipLevelChanged();

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
