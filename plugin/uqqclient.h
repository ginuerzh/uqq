#ifndef UQQCLIENT_H
#define UQQCLIENT_H

#include <QtNetwork>

class UQQClient : public QObject {

    Q_OBJECT

public:

    Q_PROPERTY(QVariantMap info READ info)
    Q_PROPERTY(int errCode READ errCode NOTIFY errCodeChanged)
    Q_PROPERTY(bool captcha READ captcha NOTIFY captchaChanged)
    UQQClient(QObject *parent = 0);
    ~UQQClient();

    void setInfo(QString key, QVariant value);
    QVariantMap info() const;

    int errCode() const;
    void setErrCode(int errCode);

    bool captcha() const;
    void setCaptcha(bool captcha);

    Q_INVOKABLE QVariant getInfo(const QString key) const;
    Q_INVOKABLE void checkCode(QString uin);
    Q_INVOKABLE void login(QString uin, QString pwd, QString vc);

private:
    void verifyCode(const QString &data);
    void getCaptcha();
    void saveCaptcha(const QByteArray &data);
    void verifyLogin(const QString &data);
    void secondLogin();
    void verifySecondLogin(const QByteArray &data);
    int parseParamList(const QString &data, QStringList &paramList);
    QString getCookie(const QString &name, QUrl url) const;

signals:
    void errCodeChanged();
    void captchaChanged();

public slots:
    void getCaptchaFinished(QNetworkReply *reply);
    void checkCodeFinished(QNetworkReply *reply);
    void loginFinished(QNetworkReply *reply);
    void secondloginFinished(QNetworkReply *reply);

private:
    QVariantMap m_infoMap;
    QNetworkAccessManager *m_manager;

    int m_errCode;
    bool m_captcha;
};

#endif // UQQCLIENT_H
