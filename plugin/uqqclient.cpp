#include "uqqclient.h"


//#define __TST

#ifdef __TST
#define TEST(func) \
    func; return;
#else
#define TEST(func)
#endif


UQQClient::UQQClient(QObject *parent)
    : QObject(parent), m_errCode(0), m_captcha(false) {

    m_manager = new QNetworkAccessManager(this);
    m_contact = new UQQContact(this);

    addLoginInfo("aid", QVariant("1003903"));  // appid
    addLoginInfo("clientid", getClientId());   // clientid

    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                    this, &UQQClient::onFinished);
}

UQQClient::~UQQClient() {
    delete m_contact;
}

void UQQClient::initConfig() {
    QString rootPath = QDir::homePath() + "/.UQQ";
    addConfig("rootPath", rootPath);  // the data root path
    QString userPath = rootPath + "/" + getLoginInfo("uin").toString();
    addConfig("userPath", userPath);
    QString facePath = userPath + "/faces";
    addConfig("facePath", facePath);    // the face images path

    QDir path;
    if (!path.mkpath(facePath))
        qDebug() << "Error: make path " << facePath;
}

void UQQClient::onFinished(QNetworkReply *reply) {
    bool ok;
    Action action = (Action)reply->request().attribute(QNetworkRequest::User).toInt(&ok);
    QString uin = reply->request().attribute(QNetworkRequest::UserMax).toString();

    if (!ok || reply->error() != QNetworkReply::NoError) {
        qWarning() << action << reply->errorString();
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
    case GetAccountAction:
        parseAccount(uin, data);
        break;
    case GetLongNickAction:
        parseLongNick(uin, data);
        break;
    case GetMemberLevelAction:
        parseMemberLevel(uin, data);
        break;
    case GetMemberInfoAction:
        parseMemberInfo(uin, data);
        break;
    case GetUserFaceAction:
        saveFace(uin, data);
        break;
    case LoadContactAction:
        parseContact(data);
        break;
    case GetOnlineBuddiesAction:
        parseOnlineBuddies(data);
        break;
    case PollMessageAction:
        parsePoll(data);
        break;
    default:
        qDebug() << "Unknown action:" << action;
    }

    reply->deleteLater();
}

void UQQClient::testCheckCode(const QString &uin) {
    addLoginInfo("uin", uin);
    addLoginInfo("vc", "!ABC");
    addLoginInfo("uinHex", "\x00\x00\x00\x00\x00\x00\x27\x10");
}

void UQQClient::checkCode(QString uin) {
    // for test
    TEST(testCheckCode(uin))
    /*
     * this doesn't work :(, the package will be sent twice, I don't why???
     *
    QUrlQuery query;
    query.setQuery("http://check.ptlogin2.qq.com/check");
    query.addQueryItem("uin", uin);
    query.addQueryItem("appid", UQQClient::AID);
    query.addQueryItem("r", "0.31415926535");
    */
    if (getLoginInfo("uin").toString() == uin) {
        qDebug() << "Same uin" << uin;
        return;
    }

    QString url = QString("http://check.ptlogin2.qq.com/check?&uin=%1&appid=%2&r=%3")
            .arg(uin, getConfig("aid").toString(), getRandom());
    QNetworkRequest request;

    addLoginInfo("uin", uin);

    request.setAttribute(QNetworkRequest::User, CheckCodeAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::verifyCode(const QString &data) {
    QStringList list;
    parseParamList(data, list);

    addLoginInfo("vc", list.at(1));
    addLoginInfo("uinHex", list.at(2).toUtf8());
    if (list.at(0).toInt() != NoError) {
        if (list.at(1).length() > 0)
            getCaptcha();
        else {
           qWarning() << data;
        }
    } else {
        emit captchaChanged(false);
    }
}

void UQQClient::testGetCaptcha() {

}

void UQQClient::getCaptcha() {
    //~ for test
    TEST(testGetCaptcha())

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

void UQQClient::testLogin(const QString &uin, const QString &pwd, const QString &vc) {
    addLoginInfo("uin", uin);
    addLoginInfo("vc", vc);
    addLoginInfo("pwd", pwd);

    UQQMember *user = new UQQMember();
    user->setUin(uin);
    user->setAccount(uin);
    m_contact->addMember(user);
    qDebug() << "testLogin:" << "login success!";
    emit loginSuccess();
}

void UQQClient::login(QString uin, QString pwd, QString vc) {
    //~ for test
    TEST(testLogin(uin, pwd, vc))

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
            .arg("away", ptwebqq,
                 getLoginInfo("clientid").toString(),
                 getLoginInfo("clientid").toString());
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

        onLoginSuccess(getLoginInfo("uin").toString(),
                       m.value("status").toString());
    } else {
        qDebug() << data;
    }
    //qDebug() << "vfwebqq=" << getLoginInfo("vfwebqq").toString();
    //qDebug() << "psessionid=" << getLoginInfo("psessionid").toString();
}

void UQQClient::onLoginSuccess(const QString &uin, const QString &status) {
    initConfig();

    UQQMember *user = new UQQMember();
    user->setUin(uin);
    user->setAccount(uin);
    user->setCategory(UQQCategory::IllegalCategory);
    user->setStatus(UQQMember::statusIndex(status));
    m_contact->addMember(user);

    //getUserFace();
    //getLongNick(uin);

    emit loginSuccess();
}

void UQQClient::testGetMemberDetail(const QString &uin) {
    testGetMemberLevel(uin);
    testGetMemberInfo(uin);
}

void UQQClient::getMemberDetail(QString uin) {
    //~ for test
    TEST(testGetMemberDetail(uin))

    getMemberLevel(uin);
    getMemberInfo(uin);
}

void UQQClient::testGetMemberAccount(const QString &uin) {
    QFile file("test/account.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseAccount(uin, data);
}

void UQQClient::getMemberAccount(const QString &uin) {
    QString url = QString("http://s.web2.qq.com/api/get_friend_uin2?tuin=%1&verifysession=&type=4&code=&vfwebqq=%2&t=%3")
            .arg(uin, getLoginInfo("vfwebqq").toString(), getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetAccountAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

/*
 *{"retcode":0,"result":{"uiuin":"","account":123456,"uin":12345668}}
 */
void UQQClient::parseAccount(const QString &uin, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();
        m_contact->member(uin)->setAccount(m.value("account").toString());

        getMemberFace(uin);
    } else {
        qDebug() << data;
    }
}

void UQQClient::testGetLongNick(const QString &uin) {
    QFile file("test/lnick.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseLongNick(uin, data);
}

void UQQClient::getLongNick(QString uin) {
    QString url = QString("http://s.web2.qq.com/api/get_single_long_nick2?tuin=%1&vfwebqq=%2&t=%3")
            .arg(uin, getLoginInfo("vfwebqq").toString(), getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetLongNickAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

/*
 * parseLongNick()
 * long nick json format:
 * {"retcode":0,"result":[{"uin":1279450562,"lnick":"123456"}]}
 */
void UQQClient::parseLongNick(const QString &uin, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    QVariantList list;
    if (m.value("retcode", DefaultError).toInt() == NoError &&
            (list = m.value("result").toList()).size() > 0) {
        m = list.at(0).toMap();
        m_contact->member(uin)->setLongnick(m.value("lnick").toString());
    } else {
        qDebug() << data;
    }
}

void UQQClient::testGetMemberLevel(const QString &uin) {
    QFile file("test/level.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseMemberLevel(uin, data);
}

void UQQClient::getMemberLevel(const QString &uin) {
    QString url = QString("http://s.web2.qq.com/api/get_qq_level2?tuin=%1&vfwebqq=%2")
            .arg(uin, getLoginInfo("vfwebqq").toString());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetMemberLevelAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}


/*
 *parseMemberLevel():
 *User Level json format:
{
    "retcode":0,
    "result":{"level":40,"days":1802,"hours":13476,"remainDays":43,"tuin":121830387}
}
*/
void UQQClient::parseMemberLevel(const QString &uin, const QByteArray &data) {
    //qDebug() << data;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    UQQMember *member;
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();
        member = m_contact->member(uin);
        member->setLevel(m.value("level").toInt());
        member->setLevelDays(m.value("days").toInt());
        member->setLevelHours(m.value("hours").toInt());
        member->setLevelRemainDays(m.value("remainDays").toInt());
    } else {
        qDebug() << data;
    }
}

void UQQClient::testGetMemberInfo(const QString &uin) {
    QFile file("test/user.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseMemberInfo(uin, data);
}

void UQQClient::getMemberInfo(const QString &uin) {
    // for test
    TEST(testGetMemberInfo(uin))

    QString url = QString("http://s.web2.qq.com/api/get_friend_info2?tuin=%1&vfwebqq=%2&t=%3")
            .arg(uin, getLoginInfo("vfwebqq").toString(), getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetMemberInfoAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

/*
{
"retcode":0,
"result":{
    "face":0,"birthday":{"month":3,"year":2013,"day":25},"occupation":"",
    "phone":"123456","allow":1,"college":"","uin":123456,"constel":1,"blood":1,
    "homepage":"","stat":0,"vip_info":0,"country":"","city":"","personal":"",
    "nick":"","shengxiao":1,"email":"","province":"","gender":"","mobile":""}
}
*/
void UQQClient::parseMemberInfo(const QString &uin, const QByteArray &data) {
    //qDebug() << data;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    UQQMember *member;
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();

        member = m_contact->member(uin);
        member->setOccupation(m.value("occupation").toString());
        member->setPhone(m.value("phone").toString());
        member->setAllow(m.value("allow").toBool());
        member->setCollege(m.value("college").toString());
        member->setConstel(m.value("constel").toInt());
        member->setBlood(m.value("blood").toInt());
        member->setHomepage(m.value("homepage").toString());
        member->setCountry(m.value("country").toString());
        member->setCity(m.value("city").toString());
        member->setPersonal(m.value("personal").toString());
        member->setNickname(m.value("nick").toString());
        member->setShengxiao(m.value("shengxiao").toInt());
        member->setEmail(m.value("email").toString());
        member->setProvince(m.value("province").toString());
        member->setGender(UQQMember::genderIndex(m.value("gender").toString()));
        member->setMobile(m.value("mobile").toString());

        m = m.value("birthday").toMap();
        member->setBirthday(m.value("year").toString() + "-" +
                            m.value("month").toString() + "-" +
                            m.value("day").toString());

    } else {
        qDebug() << data;
    }
}

void UQQClient::getUserFace() {
    getFace(getLoginInfo("uin").toString(), 1);
}

void UQQClient::getMemberFace(QString uin) {
    getFace(uin);
}

void UQQClient::getFace(const QString &uin, int cache, int type) {
    QString url = QString("http://face%1.qun.qq.com/cgi/svr/face/getface?cache=%2&type=%3&fid=0&uin=%4&vfwebqq=%5")
            .arg(QString::number(qrand() % 10 + 1), // the random domain (face1 - face10)
                 QString::number(cache), QString::number(type),
                 uin, getLoginInfo("vfwebqq").toString());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetUserFaceAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::saveFace(const QString &uin, const QByteArray &data) {
    QString facePath = getConfig("facePath").toString();
    QString account = m_contact->member(uin)->account();
    Q_ASSERT(account.length() > 0);
    QString path = facePath + "/" + account + imageFormat(data);

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(data);
    file.close();

    m_contact->member(uin)->setFace(path);

    getLongNick(uin);
}

void UQQClient::testLoadInfoCategory(int category) {
    UQQMember *member;
    QString uin;
    QList<QObject *> members = m_contact->membersInCategory(category);
    for (int i = 0; i < members.size(); i++) {
        member = (UQQMember *)members.at(i);
        uin = member->uin();
        member->setAccount(uin);
    }

}

// get friends' face images in the category index
void UQQClient::loadInfoInCategory(int category) {
    // for test
    TEST(testLoadInfoCategory(category))

    UQQMember *member;
    QString uin;
    QList<QObject *> members = m_contact->membersInCategory(category);
    for (int i = 0; i < members.size(); i++) {
        member = (UQQMember *)members.at(i);
        uin = member->uin();

        getMemberAccount(uin);
    }

}

void UQQClient::testLoadContact() {
    QFile file("test/friends.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setDataMap(m.value("result").toMap());
        testGetOnlineBuddies();
        qDebug() << "testLoadContact:" << "category ready";
        emit categoryReady();
    } else {
        qDebug() << data;
    }
}
void UQQClient::testGetOnlineBuddies() {
    QFile file("test/status.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setOnlineBuddies(m.value("result").toList());
        qDebug() << "get online buddies ok";
        //emit onlineStatusChanged();
    } else {
        qDebug() << data;
    }
}

void UQQClient::loadContact() {
    //~ for test
    TEST(testLoadContact())

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
    //~ for test
    TEST(testGetOnlineBuddies())

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
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setOnlineBuddies(m.value("result").toList());

        emit categoryReady();
    } else {
        qDebug() << data;
    }
}

void UQQClient::testPoll() {
    qDebug() << "test poll";
}

void UQQClient::poll() {
    // for test
    TEST(testPoll())

    QVariantMap param;
    QString url = QString("http://d.web2.qq.com/channel/poll2");

    param.insert("clientid", getLoginInfo("clientid"));
    param.insert("psessionid", getLoginInfo("psessionid"));
    QJsonDocument doc;
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson();
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, PollMessageAction);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "="));
}

void UQQClient::parsePoll(const QByteArray &data) {
    QString pollType;
    QVariantList result;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    int retcode = m.value("retcode", DefaultError).toInt();
    if (retcode == NoError) {
         result = m.value("result").toList();
         for (int i = 0; i < result.size(); i++) {
            m = result.at(i).toMap();
            pollType = m.value("poll_type").toString();
            m = m.value("value").toMap();
            if (pollType == "buddies_status_change") {
                //qDebug() << data;
                pollStatusChanged(m);
            } else if (pollType == "message") {
                qDebug() << data;
                pollMessage(m);
            } else if (pollType == "kick_message") {
                pollKickMessage(m);
            } else if (pollType == "group_message") {
                qDebug() << "group_message";
            } else {
                qWarning() << "Unknown poll type:" << pollType;
            }
         }

    } else if (retcode == PollNormalReturn) {
        //qDebug() << "poll normal return";
    } else if (retcode == PollOfflineError) {
        qDebug() << "Poll error:" << PollOfflineError;
    }
    else {
        qWarning() << data;
    }
}

void UQQClient::pollStatusChanged(QVariantMap m) {
    QString uin = m.value("uin").toString();
    int status = UQQMember::statusIndex(m.value("status").toString());
    int clientType = m.value("client_type").toInt();

    m_contact->setBuddyStatus(uin, status, clientType);
}

void UQQClient::pollMessage(QVariantMap m) {

}

void UQQClient::pollKickMessage(QVariantMap m) {

}

QList<QObject *> UQQClient::getCategories() {
    QList<QObject *> categories;
    QList<UQQCategory *> list = m_contact->categories();
    for (int i = 0; i < list.size(); i++) {
        categories.append(list.at(i));
    }
    return categories;
}
/*
QList<QObject *> UQQClient::getMember(QString uin) {
    QList<QObject *> members;
    members.append(m_contact->member(uin));
    //getMemberDetail(uin);
    return members;
}
*/
QList<QObject *> UQQClient::getCategoryMembers(int category) {
    QList<QObject *> list = m_contact->membersInCategory(category);

    loadInfoInCategory(category);
    return list;
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
