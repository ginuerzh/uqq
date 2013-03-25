#ifndef UQQMEMBER_H
#define UQQMEMBER_H

#include <QObject>
#include <QUrl>

class UQQMember : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString uin READ uin NOTIFY uinChanged)
    Q_PROPERTY(int account READ account NOTIFY accountChanged)
    Q_PROPERTY(int category READ category NOTIFY categoryChanged)
    Q_PROPERTY(QString markname READ markname NOTIFY marknameChanged)
    Q_PROPERTY(QString nickname READ nickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString longnick READ longnick NOTIFY longnickChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QUrl face READ face NOTIFY faceChanged)
    Q_PROPERTY(bool isVip READ isVip NOTIFY vipChanged)
    Q_PROPERTY(int vipLevel READ vipLevel NOTIFY vipLevelChanged)

    explicit UQQMember(int category = 0, QString uin = 0, QObject *parent = 0);
    
    QString uin() const;
    void setUin(QString uin);
    int account() const;
    void setAccount(int account);
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
    QString status() const;
    void setStatus(const QString &status);
    int clientType() const;
    void setClientType(int clientType);

private:
    QString m_uin;
    int m_account;
    int m_category;
    QString m_markname;
    QString m_nickname;
    QString m_longnick;
    QString m_status;
    QUrl m_face;
    bool m_vip;
    int m_vipLevel;
    int m_clientType;

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

public slots:
    
};

#endif // UQQMEMBER_H
