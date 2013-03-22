#include "uqqclient.h"

UQQClient::UQQClient(QObject *parent)
    : QObject(parent), m_errCode(0), m_captcha(false) {

    m_manager = new QNetworkAccessManager(this);
    m_contact = new UQQContact(this);

    addLoginInfo("aid", QVariant("1003903"));
    addLoginInfo("clientid", getClientId());


    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                    this, &UQQClient::onFinished);
    QObject::connect(m_contact, &UQQContact::categoryReady,
                     this, &UQQClient::categoryReady);

}

UQQClient::~UQQClient() {
    delete m_contact;
}

void UQQClient::onFinished(QNetworkReply *reply) {
    bool ok;
    Action action =
            (Action)reply->request().attribute(QNetworkRequest::User).toInt(&ok);

    if (!ok || reply->error() != QNetworkReply::NoError) {
        qDebug() << action << reply->errorString();
        return;
    }

    QByteArray data = reply->readAll();
    switch (action) {
    case CheckCodeAction:
        verifyCode(data);
        break;
    case GetCaptchaAction:
        saveCaptcha(data);
        break;
    case LoginAction:
        verifyLogin(data);
        break;
    case SecondLoginAction:
        verifySecondLogin(data);
        break;
    case GetLongNickAction:
        parseLongNick(data);
        break;
    case GetUserLevelAction:
        parseUserLevel(data);
        break;
    case GetUserDetailAction:
        parseUserDetail(data);
        break;
    case GetUserFaceAction:
        saveUserFace(data);
        break;
    case LoadContactAction:
        parseContact(data);
        break;
    case GetOnlineBuddiesAction:
        parseOnlineBuddies(data);
        break;
    default:
        qDebug() << "Unknown action:" << action;
    }

    reply->deleteLater();
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
    if (getLoginInfo("uin").toString() == uin)
        return;

    QString url = QString("http://check.ptlogin2.qq.com/check?&uin=%1&appid=%2&r=%3")
            .arg(uin, getLoginInfo("aid").toString(), getRandom());
    QNetworkRequest request;

    addLoginInfo("uin", uin);

    request.setAttribute(QNetworkRequest::User, CheckCodeAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::verifyCode(const QString &data) {
    //qDebug() << data;
    QStringList list;
    parseParamList(data, list);

    addLoginInfo("vc", list.at(1));
    addLoginInfo("uinHex", list.at(2).toUtf8());
    if (list.at(0).toInt() != NoError && list.at(1).length() > 0) {
        getCaptcha();
    } else {
        //qDebug() << data;
        emit captchaChanged(false);
    }
    //qDebug() << list;
}

void UQQClient::getCaptcha() {
    QString url = QString("http://captcha.qq.com/getimage?uin=%1&aid=%2&r=%3")
            .arg(getLoginInfo("uin").toString(),
                 getLoginInfo("aid").toString(), getRandom());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetCaptchaAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);

}

void UQQClient::saveCaptcha(const QByteArray &data) {
    QFile file("captcha" + imageFormat(data));

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(data);
    file.close();
    emit captchaChanged(true);
}

void UQQClient::login(QString uin, QString pwd, QString vc) {
    QString url = QString("http://ptlogin2.qq.com/login?u=%1&p=%2&verifycode=%3&aid=%4")
            .arg(uin, pwd, vc, getLoginInfo("aid").toString()) +
             "&webqq_type=10&remember_uin=0&login2qq=1&u1=http%3A%2F%2Fweb.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&h=1&ptredirect=0&ptlang=2052&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=2-6-22950&mibao_css=m_webqq&t=1&g=1";
    addLoginInfo("uin", uin);
    addLoginInfo("vc", vc);
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, LoginAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::verifyLogin(const QByteArray &data) {
    QStringList list;
    int errCode;
    parseParamList(data, list);

    if ((errCode = list.at(0).toInt()) == NoError) {
        secondLogin();
    } else {
        qDebug() << data;
        addLoginInfo("errMsg", list.at(4));
        if (errCode == CaptchaError) {   // get captcha again
            getCaptcha();
        }
    }
    emit errorChanged(errCode);

    //qDebug() << list;
}

void UQQClient::secondLogin() {
    QString url = "http://d.web2.qq.com/channel/login2";
    QString ptwebqq = getCookie("ptwebqq", QUrl(url));
    QString data = QString("r={\"status\":\"%1\",\"ptwebqq\":\"%2\",\"passwd_sig\":\"\",\"clientid\":\"%3\",\"psessionid\":null}"
            "&clientid=%4&psessionid=null")
            .arg("hidden", ptwebqq,
                 getLoginInfo("clientid").toString(),
                 getLoginInfo("").toString());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, SecondLoginAction);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(data, "="));
}

void UQQClient::verifySecondLogin(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();

        addLoginInfo("vfwebqq", m.value("vfwebqq"));
        addLoginInfo("psessionid", m.value("psessionid"));

        addUserInfo("status", m.value("status"));

        emit loginSuccess();    // Login successget
    } else {
        qDebug() << data;
    }
    //qDebug() << "vfwebqq=" << getLoginInfo("vfwebqq").toString();
    //qDebug() << "psessionid=" << getLoginInfo("psessionid").toString();
}

void UQQClient::loadUserInfo() {
    getUserFace();
    getLongNick();
    getUserLevel();
    getUserDetail();
}

void UQQClient::getLongNick() {
    QString url = QString("http://s.web2.qq.com/api/get_single_long_nick2?tuin=%1&vfwebqq=%2&t=%3")
            .arg(getLoginInfo("uin").toString(),
                 getLoginInfo("vfwebqq").toString(), getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetLongNickAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

/*
 * parseLongNick()
 * long nick json format:
 * {"retcode":0,"result":[{"uin":1279450562,"lnick":"123456"}]}
 */
void UQQClient::parseLongNick(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    QVariantList list;
    if (m.value("retcode", DefaultError).toInt() == NoError &&
            (list = m.value("result").toList()).size() > 0) {
        m = list.at(0).toMap();

        addUserInfo("lnick", m.value("lnick"));
        emit longNickChanged(UQQContact::mapToJson(m_userInfo));
    } else {
        qDebug() << data;
    }
}

void UQQClient::getUserLevel() {
    QString url = QString("http://s.web2.qq.com/api/get_qq_level2?tuin=%1&vfwebqq=%2")
            .arg(getLoginInfo("uin").toString(), getLoginInfo("vfwebqq").toString());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetUserLevelAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}


/*
 *parseUserLevel():
 *User Level json format:
{
    "retcode":0,
    "result":{"level":40,"days":1802,"hours":13476,"remainDays":43,"tuin":121830387}
}
*/
void UQQClient::parseUserLevel(const QByteArray &data) {
    //qDebug() << data;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_userInfo.insert("levels", m.value("result").toMap());
        emit userLevelChanged(UQQContact::mapToJson(m_userInfo));
    } else {
        qDebug() << data;
    }
}

void UQQClient::getUserDetail() {
    QString url = QString("http://s.web2.qq.com/api/get_friend_info2?tuin=%1&vfwebqq=%2&t=%3")
            .arg(getLoginInfo("uin").toString(),
                 getLoginInfo("vfwebqq").toString(),
                 getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetUserDetailAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::parseUserDetail(const QByteArray &data) {
    //qDebug() << data;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();

        m_userInfo.unite(m);
        addUserInfo("uin", getLoginInfo("uin"));    // double to string, avoid precise loss
        emit userDetailChanged(UQQContact::mapToJson(m_userInfo)); // all user info has been obtained
    } else {
        qDebug() << data;
    }
    //listUserInfo();
}

void UQQClient::listUserInfo() {
    qDebug() << "list user info:" << m_userInfo.size();
    for (QVariantMap::const_iterator ci = m_userInfo.constBegin();
         ci != m_userInfo.constEnd(); ci++) {
        qDebug() << ci.key() << ":" << ci.value();
    }
}

void UQQClient::getUserFace() {
    QString url = QString("http://face10.qun.qq.com/cgi/svr/face/getface?cache=1&type=1&fid=0&uin=%1&vfwebqq=%2")
            .arg(getLoginInfo("uin").toString(), getLoginInfo("vfwebqq").toString());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetUserFaceAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::saveUserFace(const QByteArray &data) {
    // png signature: 89:50:4e:47:0d:0a:1a:0a
    QString name = getLoginInfo("uin").toString() + imageFormat(data);
    QFile file(name);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(data);
    file.close();

    addUserInfo("facename", name);
    emit userFaceChanged(name);
}

void UQQClient::loadContact() {
    QVariantMap param;
    QString url = QString("http://s.web2.qq.com/api/get_user_friends2");

    param.insert("h", "hello");
    param.insert("vfwebqq", getLoginInfo("vfwebqq"));
    QJsonDocument doc;
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson();

    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, LoadContactAction);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "="));
}

/*
 * parseUserFriends()
 * the returned json data format:
 *   {"retcode":0,
 *       "result":{
 *           "friends":[{"flag":0,"uin":"","categories":0},...,{...}],
 *           "marknames":[{"uin":"","markname":""},...,{...}],
 *           "categories":[{"index":1,"sort":4,"name":""},...,,{...}],
 *           "vipinfo":[{"vip_level":0,"u":1234567,"is_vip":0},...,{...}],
 *           "info":[{"face":0,"flag":0,"nick":"","uin":1234567},...,{...}]
 *       }
 *   }
*/
void UQQClient::parseContact(const QByteArray &data) {
//    QFile file("friends.txt");
//    file.open(QIODevice::ReadOnly);
//    QByteArray json = file.readAll();
//    file.close();

    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setDataMap(m.value("result").toMap());
        getOnlineBuddies();
    } else {
        qDebug() << data;
    }
}

void UQQClient::getOnlineBuddies() {
    QString url = QString("http://d.web2.qq.com/channel/get_online_buddies2?clientid=%1&psessionid=%2&t=%3")
            .arg(getLoginInfo("clientid").toString(),
                 getLoginInfo("psessionid").toString(),
                 getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetOnlineBuddiesAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

/*
 * {"retcode":0,"result":[{"uin":1234567,"status":"online","client_type":1},...,{}]}
 */
void UQQClient::parseOnlineBuddies(const QByteArray &data) {
//    QFile file("status.txt");
//    file.open(QIODevice::ReadOnly);
//    QByteArray json = file.readAll();
//    file.close();

    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setOnlineBuddies(m.value("result").toList());
    } else {
        qDebug() << data;
    }
}

QString UQQClient::getFriendsInCategory(int index) {
    return UQQContact::listToJson(m_contact->getCategoryFriends(index));
}

QString UQQClient::imageFormat(const QByteArray &data) {
    QByteArray jpg = QByteArray("ffd8");
    QByteArray png = QByteArray("89504e470d0a1a0a");
    QByteArray bmp = QByteArray("424d");
    QByteArray header = data.left(8).toHex();
    //qDebug() << header.toHex();

    if (header.startsWith(png)) {
        return ".png";
    } else if (header.startsWith(jpg)) {
        return ".jpg";
    } else if (header.startsWith(bmp)) {
        return ".bmp";
    } else {
        return "";
    }
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

void UQQClient::addLoginInfo(const QString &key, const QVariant &value) {
    m_loginInfo.insert(key, value);
}
QVariant UQQClient::getLoginInfo(const QString key) const {
    return m_loginInfo.value(key, "");
}

QVariantMap UQQClient::userInfo() const {
    return m_userInfo;
}

void UQQClient::addUserInfo(const QString &key, const QVariant &value) {
    m_userInfo.insert(key, value);
}

QVariant UQQClient::getUserInfo(const QString key) const {
    return m_userInfo.value(key, "");
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

QVariant UQQClient::getConfig(const QString &key) const {
    return m_config.value(key, "");
}
void UQQClient::addConfig(const QString &key, const QVariant &value) {
    m_config.insert(key, value);
}

QString UQQClient::getClientId() {
    // JS:  = String(k.random(0, 99)) + String((new Date()).getTime() % 1000000)
    qint64 ms = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    qsrand(ms);
    int rand = qrand() % 100;
    QString id = QString::number(rand) + QString::number(ms % 1000000);
    //qDebug() << "clientId:" << id;
    return id;
}

QString UQQClient::getRandom() {
    qint64 ms = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    qsrand(ms);
    qreal r = qrand() / (qreal)ms;
    QString rs = QString::number(r, 'g', 14);
    //qDebug() << "random:" << rs;
    return rs;
}

QString UQQClient::getTimestamp() {
    qint64 ms = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    QString ts = QString::number(ms);
    //qDebug() << "timestamp:" << ts;
    return ts;
}
