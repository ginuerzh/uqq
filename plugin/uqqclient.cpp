#include "uqqclient.h"

UQQClient::UQQClient(QObject *parent)
    : QObject(parent), m_errCode(0), m_captcha(false) {
    m_manager = new QNetworkAccessManager(this);
    setInfo("aid", QVariant("1003903"));
}

UQQClient::~UQQClient() {
    delete m_manager;
}

void UQQClient::checkCode(QString uin) {
    /*
     * this doesn't work :(, the package will be sent twice, I don't why???
     *
    QUrlQuery query;
    query.setQuery("http://check.ptlogin2.qq.com/check");
    query.addQueryItem("uin", uin);
    query.addQueryItem("appid", UQQClient::AID);
    query.addQueryItem("r", "0.31415926535");
    */
    if (getInfo("uin") == uin)
        return;

    QString url = QString("http://check.ptlogin2.qq.com/check?&uin=%1&appid=%2&r=%3")
            .arg(uin, getInfo("aid").toString(), "0.5647845636556783");
    QNetworkRequest request;

    setInfo("uin", uin);

    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::checkCodeFinished);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::checkCodeFinished(QNetworkReply *reply) {
    QObject::disconnect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::checkCodeFinished);

    if (reply->error() == QNetworkReply::NoError) {
        verifyCode(reply->readAll());
    } else {
        qDebug() << reply->error() << reply->errorString();
    }
    reply->deleteLater();
}

void UQQClient::verifyCode(const QString &data) {
    //qDebug() << data;
    QStringList list;
    parseParamList(data, list);

    setInfo("vc", list.at(1));
    setInfo("uinHex", list.at(2).toUtf8());
    if (list.at(0).toInt() != 0 && list.at(1).length() > 0) {
        getCaptcha();
    } else {
        setCaptcha(false);
    }
    //qDebug() << list;
}

void UQQClient::getCaptcha() {
    QString url = QString("http://captcha.qq.com/getimage?uin=%1&aid=%2&r=%3")
            .arg(getInfo("uin").toString(), getInfo("aid").toString(), "0.34678345867123457");
    QNetworkRequest request;

    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::getCaptchaFinished);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);

}

void UQQClient::getCaptchaFinished(QNetworkReply *reply) {
    QObject::disconnect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::getCaptchaFinished);

    if (reply->error() == QNetworkReply::NoError) {
        saveCaptcha(reply->readAll());
    } else {
        qDebug() << reply->error() << reply->errorString();
    }
    reply->deleteLater();
}

void UQQClient::saveCaptcha(const QByteArray &data) {
    QFile file("captcha.jpg");

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(data);
    file.close();
    setCaptcha(true);
}

void UQQClient::login(QString uin, QString pwd, QString vc) {
    //qDebug() << "login: " << uin << ", " << pwd << ", " << vc;
    QString url = QString("http://ptlogin2.qq.com/login?u=%1&p=%2&verifycode=%3&aid=%4")
            .arg(uin, pwd, vc, getInfo("aid").toString()) +
             "&webqq_type=10&remember_uin=0&login2qq=1&u1=http%3A%2F%2Fweb.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&h=1&ptredirect=0&ptlang=2052&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=2-6-22950&mibao_css=m_webqq&t=1&g=1";

    QNetworkRequest request;

    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::loginFinished);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::loginFinished(QNetworkReply *reply) {
    QObject::disconnect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::loginFinished);

    if (reply->error() == QNetworkReply::NoError) {
        verifyLogin(reply->readAll());
    } else {
        qDebug() << reply->error() << reply->errorString();
    }
    reply->deleteLater();
}

void UQQClient::verifyLogin(const QString &data) {
    //qDebug() << data;
    QStringList list;
    int errCode;
    parseParamList(data, list);

    setInfo("vc", list.at(1));
    setInfo("uinHex", list.at(2));
    if ((errCode = list.at(0).toInt()) == 0) {
        secondLogin();
    } else {
        setInfo("errMsg", list.at(4));
    }
    setErrCode(errCode);
    //qDebug() << list;
}

void UQQClient::secondLogin() {
    QString url = "http://d.web2.qq.com/channel/login2";
    QString ptwebqq = getCookie("ptwebqq", QUrl(url));
    QString data = QString("r={\"status\":\"%1\",\"ptwebqq\":\"%2\",\"passwd_sig\":\"\",\"clientid\":\"25499193\",\"psessionid\":null}"
            "&clientid=25499193&psessionid=null")
            .arg("hidden", ptwebqq);
    QNetworkRequest request;

    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::secondloginFinished);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(data, "="));
}

void UQQClient::secondloginFinished(QNetworkReply *reply) {
    QObject::disconnect(m_manager, &QNetworkAccessManager::finished,
                     this, &UQQClient::secondloginFinished);

    if (reply->error() == QNetworkReply::NoError) {
        verifySecondLogin(reply->readAll());
    } else {
        qDebug() << reply->error() << reply->errorString();
    }
    reply->deleteLater();
}

void UQQClient::verifySecondLogin(const QByteArray &data) {
    QJsonObject o;
    QJsonValue value;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    if (err.error == QJsonParseError::NoError) {
        if (doc.isObject()) {
            o = doc.object();
            QJsonValue v = o.value("result");
            if (!v.isUndefined() && v.isObject()) {
                o = v.toObject();
                value = o.value("vfwebqq");
                if (!value.isUndefined() && value.isString()) {
                    setInfo("vfwebqq", value.toString());
                }
                value = o.value("psessionid");
                if (!value.isUndefined() && value.isString()) {
                    setInfo("psessionid", value.toString());
                }
            }
        }
    } else {
        qDebug() << "err: " << err.errorString();
    }
    //qDebug() << "vfwebqq=" << getInfo("vfwebqq").toString();
    //qDebug() << "psessionid=" << getInfo("psessionid").toString();
}

int UQQClient::parseParamList(const QString &data, QStringList &paramList) {
    int begIndex = data.indexOf("(");
    int endIndex = data.lastIndexOf(")");

    QStringList list = data.mid(begIndex + 1, endIndex - begIndex - 1).split(",");
    for (int i = 0; i < list.size(); i++) {
        QString str = list.at(i).trimmed();
        // remove the "'" around the string
        list.replace(i, str.mid(1, str.length() - 2));
    }
    paramList << list;
    return list.size();
}

void UQQClient::setInfo(QString key, QVariant value) {
    m_infoMap.insert(key, value);
}
QVariant UQQClient::getInfo(const QString key) const {
    return m_infoMap.value(key);
}
QVariantMap UQQClient::info() const {
    return m_infoMap;
}

int UQQClient::errCode() const {
    return m_errCode;
}
void UQQClient::setErrCode(int errCode) {
    if (errCode != m_errCode) {
        m_errCode = errCode;
        emit errCodeChanged();
    }
}

bool UQQClient::captcha() const {
    return m_captcha;
}
void UQQClient::setCaptcha(bool captcha) {
    if (m_captcha != captcha) {
        m_captcha = captcha;
        emit captchaChanged();
    }
}

QString UQQClient::getCookie(const QString &name, QUrl url) const {
    QList<QNetworkCookie> cookies = m_manager->cookieJar()->cookiesForUrl(url);
    //qDebug() << url.toString();
    for (int i = 0; i < cookies.size(); i++) {
        //qDebug() << "name:" << cookies.at(i).name() << ", value:" << cookies.at(i).value();
        if (cookies.at(i).name() == name) {
            return cookies.at(i).value();
        }
    }
    return "";
}
