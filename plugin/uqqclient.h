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
        GetUserLevelAction,
        GetUserDetailAction,
        GetUserFaceAction,
        LoadContactAction,
        GetOnlineBuddiesAction
    };

    enum Error {
        NoError,
        PasswordError = 3,
        CaptchaError,
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
    Q_INVOKABLE void loadUserInfo();
    Q_INVOKABLE void loadContact();
    Q_INVOKABLE QString getFriendsInCategory(int index);

private:
    void verifyCode(const QString &data);
    void getCaptcha();
    void saveCaptcha(const QByteArray &data);
    void verifyLogin(const QByteArray &data);
    void secondLogin();
    void verifySecondLogin(const QByteArray &data);

    void getLongNick();
    void parseLongNick(const QByteArray &data);
    void getUserLevel();
    void parseUserLevel(const QByteArray &data);
    void getUserDetail();
    void parseUserDetail(const QByteArray &data);
    void getUserFace();
    void saveUserFace(const QByteArray &data);
    void parseContact(const QByteArray &data);
    void getOnlineBuddies();
    void parseOnlineBuddies(const QByteArray &data);

    QVariant getConfig(const QString &key) const;
    void addConfig(const QString &key, const QVariant &value);

    int parseParamList(const QString &data, QStringList &paramList);
    QString getCookie(const QString &name, QUrl url) const;

    QString getClientId();
    QString getRandom();
    QString getTimestamp();
    QString imageFormat(const QByteArray &data);

    void listUserInfo();

signals:
    void errorChanged(int errCode);
    void captchaChanged(bool needed);
    void loginSuccess();
    void userFaceChanged(QString face);
    void longNickChanged(QString json);
    void userLevelChanged(QString json);
    void userDetailChanged(QString json);
    void categoryReady(QString json);

public slots:
    void onFinished(QNetworkReply *reply);

private:
    QVariantMap m_loginInfo;
    QVariantMap m_userInfo;
    QVariantMap m_config;
    QNetworkAccessManager *m_manager;

    UQQContact *m_contact;

    int m_errCode;
    bool m_captcha;
};

#endif // UQQCLIENT_H
