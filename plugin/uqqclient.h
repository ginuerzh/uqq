#ifndef UQQCLIENT_H
#define UQQCLIENT_H

#include <QtNetwork>
#include "uqqcontact.h"

class UQQClient : public QObject {

    Q_OBJECT
public:
    enum Action {
        // Login phase actions
        CheckCodeAction,
        GetCaptchaAction,
        LoginAction,
        SecondLoginAction,

        // After login
        GetLongNickAction = 10,
        GetAccountAction,
        GetMemberLevelAction,
        GetMemberInfoAction,
        GetUserFaceAction,
        LoadContactAction,
        GetOnlineBuddiesAction,
        PollMessageAction
    };

    enum Error {
        NoError,
        PasswordError = 3,
        CaptchaError,
        PollNormalReturn = 102,
        PollOfflineError,
        DefaultError = 10000
    };

    //Q_PROPERTY(QVariantMap userInfo READ userInfo NOTIFY userInfoChanged)

    explicit UQQClient(QObject *parent = 0);
    ~UQQClient();

    void addLoginInfo(const QString &key, const QVariant &value);
    Q_INVOKABLE QVariant getLoginInfo(const QString key) const;

    QVariantMap userInfo() const;
    void addUserInfo(const QString &key, const QVariant &value);
    Q_INVOKABLE QVariant getUserInfo(const QString key) const;

    Q_INVOKABLE void checkCode(QString uin);
    Q_INVOKABLE void login(QString uin, QString pwd, QString vc);
    Q_INVOKABLE void getMemberDetail(QString uin);
    Q_INVOKABLE void loadContact();
    Q_INVOKABLE QList<QObject *> getCategories();
    Q_INVOKABLE QList<QObject *> getCategoryMembers(int category);
    //Q_INVOKABLE QList<QObject *> getMember(QString uin);
    Q_INVOKABLE void loadInfoInCategory(int category);
    Q_INVOKABLE void getMemberFace(QString uin);
    Q_INVOKABLE void getOnlineBuddies();
    Q_INVOKABLE void poll();

private:
    void initConfig();
    QVariant getConfig(const QString &key) const;
    void addConfig(const QString &key, const QVariant &value);

    void verifyCode(const QString &data);
    void getCaptcha();
    void saveCaptcha(const QByteArray &data);
    void verifyLogin(const QByteArray &data);
    void secondLogin();
    void verifySecondLogin(const QByteArray &data);

    void getLongNick(QString uin);
    void parseLongNick(const QString &uin, const QByteArray &data);
    void getMemberLevel(const QString &uin);
    void parseMemberLevel(const QString &uin, const QByteArray &data);
    void getMemberInfo(const QString &uin);
    void parseMemberInfo(const QString &uin, const QByteArray &data);
    void getUserFace();
    void getMemberAccount(const QString &uin);
    void parseAccount(const QString &uin, const QByteArray &data);
    void getFace(const QString &uin, int cache = 0, int type = 1);
    void saveFace(const QString &uin, const QByteArray &data);
    void parseContact(const QByteArray &data);
    void parseOnlineBuddies(const QByteArray &data);

    int parseParamList(const QString &data, QStringList &paramList);
    QString getCookie(const QString &name, QUrl url) const;

    QString getClientId();
    QString getRandom();
    QString getTimestamp();
    QString imageFormat(const QByteArray &data);

    void onLoginSuccess(const QString &uin, const QString &status);

    void parsePoll(const QByteArray &data);
    void pollStatusChanged(QVariantMap m);
    void pollMessage(QVariantMap m);
    void pollKickMessage(QVariantMap m);

    // for test
    void testCheckCode(const QString &uin);
    void testGetCaptcha();
    void testLoadContact();
    void testGetOnlineBuddies();
    void testLogin(const QString &uin, const QString &pwd, const QString &vc);
    void testGetMemberDetail(const QString &uin);
    void testGetMemberAccount(const QString &uin);
    void testGetMemberLevel(const QString &uin);
    void testGetLongNick(const QString &uin);
    void testGetMemberInfo(const QString &uin);
    void testLoadInfoCategory(int category);
    void testPoll();

signals:
    void errorChanged(int errCode);
    void captchaChanged(bool needed);
    void loginSuccess();
    void categoryReady();
    void onlineStatusChanged();

public slots:
    void onFinished(QNetworkReply *reply);

private:
    QVariantMap m_loginInfo;
    QVariantMap m_config;
    QNetworkAccessManager *m_manager;

    UQQContact *m_contact;

    int m_errCode;
    bool m_captcha;
};

#endif // UQQCLIENT_H
