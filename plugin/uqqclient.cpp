#include "uqqclient.h"
#include "uqqmemberdetail.h"

#ifdef UQQ_TEST
#define TEST(func) \
    func; return;
#else
#define TEST(func)
#endif

UQQClient::UQQClient(QObject *parent)
    : QObject(parent) {

    m_contact = Q_NULLPTR;
    m_group = Q_NULLPTR;

    initClient();

#ifndef UQQ_TEST
    m_manager = new QNetworkAccessManager(this);
    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                    this, &UQQClient::onFinished);
#endif

    addLoginInfo("aid", QVariant("1003903"));  // appid
    addLoginInfo("clientid", getClientId());   // clientid
}

UQQClient::~UQQClient() {
    delete m_contact;
}

void UQQClient::initClient() {
    if (m_contact) {
        delete m_contact;
    }
    m_contact = new UQQContact(this);

    if (m_group) {
        delete m_group;
    }
    m_group = new UQQGroup(this);
}

void UQQClient::initConfig() {
    QString rootPath = QDir::homePath() + "/.UQQ";
    addConfig("rootPath", rootPath);  // the data root path
    QString userPath = rootPath + "/" + getLoginInfo("uin").toString();
    addConfig("userPath", userPath);
    QString groupPath = userPath + "/group";   // the group path
    addConfig("groupPath", groupPath);
    QString groupFacePath = groupPath + "/faces";
    addConfig("groupfacePath", groupFacePath);  // the group face images path
    QString facePath = userPath + "/faces";
    addConfig("facePath", facePath);    // the face images path

    QDir path;
    if (!path.mkpath(facePath) || !path.mkpath(groupPath) || !path.mkpath(groupFacePath))
        qCritical() << "Error: make path";
}

void UQQClient::onFinished(QNetworkReply *reply) {
    bool ok;
    Action action = (Action)reply->request().attribute(QNetworkRequest::User).toInt(&ok);
    QVariant p0 = reply->request().attribute(QNetworkRequest::Attribute(QNetworkRequest::User + 1));
    QVariant p = reply->request().attribute(QNetworkRequest::UserMax);

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
    case LogoutAction:
        parseLogout(data);
        break;
    case SecondLoginAction:
        verifySecondLogin(data);
        break;
    case GetMemberAccountAction:
        parseAccount(p0.toULongLong(), p.toString(), data, GetMemberAccountAction);
        break;
    case GetGroupAccountAction:
        parseAccount(p0.toULongLong(), p.toString(), data, GetGroupAccountAction);
        break;
    case GetLongNickAction:
        parseLongNick(p0.toULongLong(), p.toString(), data);
        break;
    case GetMemberLevelAction:
        parseMemberLevel(p.toString(), data);
        break;
    case GetMemberInfoAction:
        parseMemberInfo(p.toString(), data);
        break;
    case GetStrangerInfoAction:
        parseStrangerInfo(p0.toULongLong(), p.toString(), data);
        break;
    case GetUserFaceAction:
        saveFace(p0.toULongLong(), p.toString(), data);
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
    case SendBuddyMessageAction:
        parseMessage(p.toString(), data);
        break;
    case SendGroupMessageAction:
        parseMessage(p.toString(), data);
        break;
    case SendSessionMessageAction:
        parseMessage(p.toString(), data);
        break;
    case ChangeStatusAction:
        parseChangeStatus(p.toString(), data);
        break;
    case LoadGroupsAction:
        parseGroups(data);
        break;
    case LoadGroupInfoAction:
        parseGroupInfo(p.toULongLong(), data);
        break;
    case GetGroupSigAction:
        parseGroupSig(p0.toULongLong(),
                      p.toString(),
                      data);
        break;
    default:
        qWarning() << "Unknown action:" << action;
    }

    reply->deleteLater();
}

void UQQClient::testCheckCode(const QString &uin) {
    addLoginInfo("uin", uin);
    addLoginInfo("vc", "!ABC");
    addLoginInfo("uinHex", "\x00\x00\x00\x00\x00\x00\x27\x10");
}

void UQQClient::checkCode(QString uin) {
    qDebug() << "check code...";
    TEST(testCheckCode(uin));

    QUrl url("http://check.ptlogin2.qq.com/check");
    QUrlQuery query;
    query.addQueryItem("uin", uin);
    query.addQueryItem("appid", getLoginInfo("aid").toString());
    query.addQueryItem("r", getRandom());
    url.setQuery(query);

    qDebug() << url.toString();

    QNetworkRequest request;

    addLoginInfo("uin", uin);

    request.setAttribute(QNetworkRequest::User, CheckCodeAction);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::verifyCode(const QString &data) {
    QStringList list;
    parseParamList(data, list);

    addLoginInfo("vc", list.at(1));
    addLoginInfo("uinHex", list.at(2).toUtf8());
    if (list.at(0).toInt() != NoError) {
        if (list.at(1).length() > 0) {
            qDebug() << "check code done, code needed.";
            getCaptcha();
        }
        else {
           qWarning() << data;
        }
    } else {
        qDebug() << "check code done, code no needed.";
        emit captchaChanged(false);
    }
}

void UQQClient::testGetCaptcha() {

}

void UQQClient::getCaptcha() {
    qDebug() << "get captcha...";
    TEST(testGetCaptcha());

    QUrl url("http://captcha.qq.com/getimage");
    QUrlQuery query;
    query.addQueryItem("uin", getLoginInfo("uin").toString());
    query.addQueryItem("aid", getLoginInfo("aid").toString());
    query.addQueryItem("r", getRandom());
    url.setQuery(query);
    qDebug() << url.toString();

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, GetCaptchaAction);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);

}

void UQQClient::saveCaptcha(const QByteArray &data) {
    QFile file("captcha" + imageFormat(data));

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(data);
    file.close();
    qDebug() << "get captcha done, captcha saved.";
    emit captchaChanged(true);
}

void UQQClient::logout() {

    QString url = QString("/channel/logout2?ids=&clientid=%1&psessionid=%2&t=%3")
            .arg(getLoginInfo("clientid").toString(),
                 getLoginInfo("psessionid").toString(),
                 getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, LogoutAction);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::parseLogout(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    int retcode = m.value("retcode", DefaultError).toInt();
    if (retcode == NoError) {
        qDebug() << "logout ok";
    } else {
        qWarning() << "parseLogout:" << data;
    }
}

void UQQClient::testLogin(const QString &pwd, const QString &vc, const QString &status) {
    QString uin = "121830387";
    addLoginInfo("uin", uin);
    addLoginInfo("vc", vc);
    addLoginInfo("pwd", pwd);
    addLoginInfo("status", status);

    onLoginSuccess(getLoginInfo("uin").toString(), status);

    qDebug() << "testLogin:" << "login success!";
}

void UQQClient::login(QString uin, QString pwd, QString vc, QString status) {
    qDebug() << "request login...";
    TEST(testLogin(pwd, vc, status));

    QUrl url("http://ptlogin2.qq.com/login");
    //QUrl u1("http://web.qq.com/loginproxy.html?login2qq=1&webqq_type=10");
    QUrlQuery query;
    query.addQueryItem("u", uin);
    query.addQueryItem("p", pwd);
    query.addQueryItem("verifycode", vc);
    query.addQueryItem("aid", getLoginInfo("aid").toString());
    query.addQueryItem("webqq_type", QString::number(10));
    query.addQueryItem("remember_uin", QString::number(0));
    query.addQueryItem("login2qq", QString::number(1));
    //query.addQueryItem("u1", u1.toEncoded());
    query.addQueryItem("h", QString::number(1));
    query.addQueryItem("ptredirect", QString::number(0));
    query.addQueryItem("ptlang", QString::number(2052));
    query.addQueryItem("from_ui", QString::number(1));
    query.addQueryItem("pttype", QString::number(1));
    query.addQueryItem("fp", "loginerroralert");
    query.addQueryItem("action", "2-6-22950");
    query.addQueryItem("mibao_css", "m_webqq");
    query.addQueryItem("t", QString::number(1));
    query.addQueryItem("g", QString::number(1));
    url.setQuery(query);
    url = QUrl(url.toString().append("&u1=http%3A%2F%2Fweb.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10"));
    qDebug() << url.toString();

    addLoginInfo("uin", uin);
    addLoginInfo("vc", vc);
    addLoginInfo("pwd", pwd);
    addLoginInfo("status", status);

    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, LoginAction);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::verifyLogin(const QByteArray &data) {
    QStringList list;
    int errCode;
    parseParamList(data, list);

    if ((errCode = list.at(0).toInt()) == NoError) {
        qDebug() << "login done.";
        secondLogin();
    } else {
        qWarning() << data;
        addLoginInfo("errMsg", list.at(4));
        if (errCode == CaptchaError) {   // get captcha again
            getCaptcha();
        }
    }
    emit errorChanged(errCode);
}

void UQQClient::autoReLogin() {
    TEST(onLoginSuccess(getLoginInfo("uin").toString(), getLoginInfo("status").toString()));

    secondLogin();
}

void UQQClient::secondLogin() {
    qDebug() << "request second login...";

    QUrl url("http://d.web2.qq.com/channel/login2");
    qDebug() << url.toString();

    QString ptwebqq = getCookie("ptwebqq", url);
    addLoginInfo("ptwebqq", ptwebqq);
    qDebug() << "ptwebqq:" << ptwebqq;

    QVariantMap param;
    param.insert("status", getLoginInfo("status").toString());
    param.insert("ptwebqq", ptwebqq);
    param.insert("passwd_sig", "");
    param.insert("clientid", getLoginInfo("clientid").toString());
    param.insert("psessionid", getLoginInfo("psessionid").toString());
    QJsonDocument doc;
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson();
    p.append(QString("&clientid=%1&psessionid=%2")
             .arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));


    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, SecondLoginAction);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));
}

void UQQClient::verifySecondLogin(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();

        addLoginInfo("vfwebqq", m.value("vfwebqq"));
        addLoginInfo("psessionid", m.value("psessionid"));
        addLoginInfo("status", m.value("status").toString());

        qDebug() << "second login done.";

        onLoginSuccess(getLoginInfo("uin").toString(),
                       m.value("status").toString());

    } else {
        qDebug() << data;
    }
}

void UQQClient::onLoginSuccess(const QString &uin, const QString &status) {
    initClient();
    initConfig();

    UQQMember *user = new UQQMember(UQQCategory::IllegalCategoryId, uin, m_contact);
    qDebug() << "login success! status:" << status;
    user->setStatus(UQQMember::statusIndex(status));
    m_contact->addMember(user);

    qDebug() << "get user" << uin << "information";
    getUserFace();
    getLongNick(UQQCategory::IllegalCategoryId, uin);
    getMemberDetail(UQQCategory::IllegalCategoryId, uin);

    loadContact();
}

void UQQClient::getSimpleInfo(quint64 gid, QString uin) {
    getFace(gid, uin);

    UQQMember *member = this->member(gid, uin);
    Q_CHECK_PTR(member);
    if (member && member->isFriend())
        getLongNick(gid, uin);
}

void UQQClient::getMemberDetail(quint64 gid, QString uin) {
    UQQMember *member = this->member(gid, uin);
    Q_CHECK_PTR(member);
    if (!member) return;

    if (member->isFriend()) {
        getMemberInfo(uin);
        getMemberLevel(uin);
    } else {
        getStrangerInfo(gid, uin);
        if (member->groupSig().isEmpty())
            getGroupSig(gid, uin);
    }
    getMemberAccount(gid, uin);

}

void UQQClient::testGetAccount(quint64 gid, const QString &uin, Action action) {
    QFile file("test/account.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseAccount(gid, uin, data, action);
}

void UQQClient::getMemberAccount(quint64 gid, const QString &uin) {
    getAccount(gid, uin, GetMemberAccountAction);
}

void UQQClient::getGroupAccount(const QString &uin) {
    qDebug() << "request group account...";
    getAccount(UQQCategory::IllegalCategoryId, uin, GetGroupAccountAction);
}

void UQQClient::getAccount(quint64 gid, const QString &uin, Action action) {
    qDebug() << "get account...";
    TEST(testGetAccount(gid, uin, action));

    QUrl url("http://s.web2.qq.com/api/get_friend_uin2");
    QUrlQuery query;
    query.addQueryItem("tuin", uin);
    query.addQueryItem("verifysession", "");
    query.addQueryItem("type", QString::number(1));
    query.addQueryItem("code", "");
    query.addQueryItem("vfwebqq", getLoginInfo("vfwebqq").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    qDebug() << url.toString();

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, action);
    request.setAttribute(QNetworkRequest::Attribute(QNetworkRequest::User + 1), gid);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->get(request);
}

/*
 *{"retcode":0,"result":{"uiuin":"","account":123456,"uin":12345668}}
 */
void UQQClient::parseAccount(quint64 gid, const QString &uin, const QByteArray &data, Action action) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();

        if (action == GetMemberAccountAction) {
            UQQMember *member = this->member(gid, uin);
            Q_CHECK_PTR(member);
            if (!member) return;
            UQQMemberDetail *detail = Q_NULLPTR;
            if ((detail = member->detail()) == Q_NULLPTR) {
                detail = new UQQMemberDetail(member);
                member->setDetail(detail);
            }
            member->detail()->setAccount(m.value("account").toULongLong());
            qDebug() << "get account done." << member->detail()->account();
        } else {
            UQQCategory *group = m_group->getGroupByCode(uin.toULongLong());
            Q_CHECK_PTR(group);
            if (group) {
                group->setAccount(m.value("account").toULongLong());
                qDebug() << "request group account done, group" << gid << "account:" << group->account();
            }
        }
    } else {
        qDebug() << "parseAccount:" << data;
    }
}

void UQQClient::testGetLongNick(quint64 gid, const QString &uin) {
    QFile file("test/lnick.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseLongNick(gid, uin, data);
}

void UQQClient::getLongNick(quint64 gid, const QString &uin) {
    TEST(testGetLongNick(gid, uin));

    QUrl url("http://s.web2.qq.com/api/get_single_long_nick2");
    QUrlQuery query;
    query.addQueryItem("tuin", uin);
    query.addQueryItem("vfwebqq", getLoginInfo("vfwebqq").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    //qDebug() << url.toString();

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, GetLongNickAction);
    request.setAttribute(QNetworkRequest::Attribute(QNetworkRequest::User + 1), gid);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

/*
 * parseLongNick()
 * long nick json format:
 * {"retcode":0,"result":[{"uin":1279450562,"lnick":"123456"}]}
 */
void UQQClient::parseLongNick(quint64 gid, const QString &uin, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    QVariantList list;
    UQQMember *member = Q_NULLPTR;
    if (m.value("retcode", DefaultError).toInt() == NoError &&
            (list = m.value("result").toList()).size() > 0) {
        m = list.at(0).toMap();
        member = this->member(gid, uin);
        Q_CHECK_PTR(member);
        if (member)
            member->setLongnick(m.value("lnick").toString());
    } else {
        qDebug() << "parseLongNick:" << data;
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
    TEST(testGetMemberLevel(uin));

    QUrl url("http://s.web2.qq.com/api/get_qq_level2");
    QUrlQuery query;
    query.addQueryItem("tuin", uin);
    query.addQueryItem("vfwebqq", getLoginInfo("vfwebqq").toString());
    url.setQuery(query);
    qDebug() << url.toString();

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, GetMemberLevelAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(url);
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
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    UQQMember *member = Q_NULLPTR;
    UQQMemberDetail *detail = Q_NULLPTR;

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();
        member = m_contact->member(uin);
        Q_CHECK_PTR(member);

        if ((detail = member->detail()) == Q_NULLPTR) {
            detail = new UQQMemberDetail(member);
            member->setDetail(detail);
        }
        member->detail()->setLevel(m.value("level").toInt());
        member->detail()->setLevelDays(m.value("days").toInt());
        member->detail()->setLevelHours(m.value("hours").toInt());
        member->detail()->setLevelRemainDays(m.value("remainDays").toInt());
    } else {
        qDebug() << "parseMemberLevel:" << data;
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
    TEST(testGetMemberInfo(uin));

    QUrl url("http://s.web2.qq.com/api/get_friend_info2");
    QUrlQuery query;
    query.addQueryItem("tuin", uin);
    query.addQueryItem("vfwebqq", getLoginInfo("vfwebqq").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    qDebug() << url.toString();

    //QString url = QString("http://s.web2.qq.com/api/get_friend_info2?tuin=%1&vfwebqq=%2&t=%3")
    //        .arg(uin, getLoginInfo("vfwebqq").toString(), getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetMemberInfoAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
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
    UQQMember *member = Q_NULLPTR;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        member = this->member(UQQCategory::IllegalCategoryId, uin);
        Q_CHECK_PTR(member);
        if (member)
            setMemberDetail(member, m.value("result").toMap());
    } else {
        qDebug() << "parseMemberInfo:" << data;
    }
}

void UQQClient::testGetStrangerInfo(quint64 gid, const QString &uin) {
    QFile file("test/user.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseStrangerInfo(gid, uin, data);
}

void UQQClient::getStrangerInfo(quint64 gid, const QString &uin) {
    qDebug() << "get stranger info...";
    TEST(testGetStrangerInfo(gid, uin));

    QUrl url("http://s.web2.qq.com/api/get_stranger_info2");
    QUrlQuery query;
    query.addQueryItem("tuin", uin);
    query.addQueryItem("vfwebqq", getLoginInfo("vfwebqq").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    qDebug() << url.toString();

    //QString url = QString("http://s.web2.qq.com/api/get_stranger_info2?tuin=%1&verifysession=&gid=0&code=&vfwebqq=%2&t=%3")
    //        .arg(uin,
    //             getLoginInfo("vfwebqq").toString(),
    //             getTimestamp());

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, GetStrangerInfoAction);
    request.setAttribute(QNetworkRequest::Attribute(QNetworkRequest::User + 1), gid);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->get(request);
}

void UQQClient::parseStrangerInfo(quint64 gid, const QString &uin, const QByteArray &data) {
    UQQMember *member = Q_NULLPTR;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        if ((member = this->member(gid, uin)) == Q_NULLPTR) {
            member = new UQQMember(gid, uin, m_contact);
            QList<UQQMessage *> messages = m_contact->getSessMessage(uin);
            UQQMessage *message;
            foreach(message, messages) {
                message->setParent(member);
                member->addMessage(message);
            }
            m_contact->addMember(member);
        }
        qDebug() << "get stranger info done.";
        setMemberDetail(member, m.value("result").toMap());
    } else {
        qDebug() << "parseStrangerInfo:" << data;
    }
}

void UQQClient::setMemberDetail(UQQMember *member, const QVariantMap &m) {
    UQQMemberDetail *detail = Q_NULLPTR;
    qDebug() << "set member detail...";
    member->setNickname(m.value("nick").toString());
    //member->setStatus(m.value("stat").toInt() / 10);

    if ((detail = member->detail()) == Q_NULLPTR)
        detail = new UQQMemberDetail(member);

    detail->setFaceid(m.value("face").toInt());
    detail->setOccupation(m.value("occupation").toString());
    detail->setPhone(m.value("phone").toString());
    detail->setAllow(m.value("allow").toBool());
    detail->setCollege(m.value("college").toString());
    detail->setConstel(m.value("constel").toInt());
    detail->setBlood(m.value("blood").toInt());
    detail->setHomepage(m.value("homepage").toString());
    detail->setCountry(m.value("country").toString());
    detail->setCity(m.value("city").toString());
    detail->setPersonal(m.value("personal").toString());
    member->setNickname(m.value("nick").toString());    // nickname not in detail
    detail->setShengxiao(m.value("shengxiao").toInt());
    detail->setEmail(m.value("email").toString());
    detail->setProvince(m.value("province").toString());
    detail->setGender(UQQMemberDetail::genderIndex(m.value("gender").toString()));
    detail->setMobile(m.value("mobile").toString());
    detail->setToken(m.value("token").toString());

    QVariantMap birth = m.value("birthday").toMap();
    int year = birth.value("year").toInt();
    int month = birth.value("month").toInt();
    int day = birth.value("day").toInt();
    if (QDate::isValid(year, month, day)) {
        QDateTime birth;
        birth.setDate(QDate(year, month, day));
        detail->setBirthday(birth);
    }

    member->setDetail(detail);
    qDebug() << "set member detail done.";
}

UQQMember *UQQClient::member(quint64 gid, const QString &uin) {
    UQQMember *member = Q_NULLPTR;
    UQQCategory *cat = Q_NULLPTR;

    if ((member = m_contact->member(uin)) == Q_NULLPTR) {
        if ((cat = m_group->getGroupById(gid)) != Q_NULLPTR) {
            member = cat->member(uin);
        }
    }
    return member;
}

void UQQClient::getUserFace() {
    getFace(UQQCategory::IllegalCategoryId, getLoginInfo("uin").toString(), 1);
}

void UQQClient::testGetFace(quint64 gid, const QString &uin) {
    QString path = "../121830387.bmp";
    UQQMember *member = this->member(gid, uin);
    Q_CHECK_PTR(member);
    if (member) member->setFace(path);
}

void UQQClient::getFace(quint64 gid, const QString &uin, int cache, int type) {
    TEST(testGetFace(gid, uin));

    QUrl url(QString("http://face%1.qun.qq.com/cgi/svr/face/getface").arg(QString::number(qrand() % 10 + 1)));
    QUrlQuery query;
    query.addQueryItem("cache", QString::number(cache));
    query.addQueryItem("type", QString::number(type));
    query.addQueryItem("uin", uin);
    query.addQueryItem("vfwebqq", getLoginInfo("vfwebqq").toString());
    url.setQuery(query);
    //qDebug() << url.toString();

    //QString url = QString("http://face%1.qun.qq.com/cgi/svr/face/getface?cache=%2&type=%3&fid=0&uin=%4&vfwebqq=%5")
    //        .arg(QString::number(qrand() % 10 + 1), // the random domain (face1 - face10)
    //             QString::number(cache), QString::number(type),
    //             uin, getLoginInfo("vfwebqq").toString());

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, GetUserFaceAction);
    request.setAttribute(QNetworkRequest::Attribute(QNetworkRequest::User + 1), gid);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::saveFace(quint64 gid, const QString &uin, const QByteArray &data) {
    QString facePath = getConfig("facePath").toString();
    UQQMember *member = this->member(gid, uin);
    Q_CHECK_PTR(member);
    if (!member) return;
    QString path = facePath + "/" + uin + imageFormat(data);

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(data);
    file.close();

    member->setFace(path);
}

void UQQClient::testChangeStatus(const QString &status) {
    QString uin = getLoginInfo("uin").toString();
    UQQMember *user = m_contact->member(uin);
    if (user)
        user->setStatus(UQQMember::statusIndex(status));
}

void UQQClient::changeStatus(QString status) {
    TEST(testChangeStatus(status));

    QUrl url("http://d.web2.qq.com/channel/change_status2");
    QUrlQuery query;
    query.addQueryItem("newstatus", status);
    query.addQueryItem("clientid", getLoginInfo("clientid").toString());
    query.addQueryItem("psessionid", getLoginInfo("psessionid").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    qDebug() << url.toString();

    //QString url = QString("http://d.web2.qq.com/channel/change_status2?newstatus=%1&clientid=%2&psessionid=%3&t=%4")
    //        .arg(status,
    //             getLoginInfo("clientid").toString(),
    //             getLoginInfo("psessionid").toString(),
    //             getTimestamp());

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, ChangeStatusAction);
    request.setAttribute(QNetworkRequest::UserMax, status);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::parseChangeStatus(const QString &status, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    int retcode = m.value("retcode", DefaultError).toInt();
    if (retcode == NoError) {
        qDebug() << "change status ok:" << status;
        QString uin = getLoginInfo("uin").toString();
        UQQMember *user = m_contact->member(uin);
        if (user) {
            user->setStatus(UQQMember::statusIndex(status));
            addLoginInfo("status", status);
        }

    } else {
        qWarning() << "parseChangeStatus:" << data;
    }
}

void UQQClient::testLoadContact() {
    QFile file("test/friends.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseContact(data);
}

QString UQQClient::hashFriends(char *uin, char *ptwebqq) {
    size_t len = strlen(ptwebqq)+strlen("password error")+3;
    char* a = (char *)malloc(len);
    memset(a, 0, len);
    const char* b = uin;
    strcat(strcpy(a,ptwebqq),"password error");
    size_t alen = strlen(a);
    len = 2048;
    char* s = (char *)malloc(len);
    memset(s, 0, len);
    int *j = (int *)malloc(sizeof(int)*alen);
    for(;;){
        if(strlen(s)<=alen){
            if(strcat(s,b),strlen(s)==alen) break;
        }else{
            s[alen]='\0';
            break;
        }
    }
    size_t d;
    for(d=0;d<strlen(s);d++){
        j[d]=s[d]^a[d];
    }
    const char* ch = "0123456789ABCDEF";
    s[0]=0;
    for(d=0;d<alen;d++){
        s[2*d]=ch[j[d]>>4&15];
        s[2*d+1]=ch[j[d]&15];
    }
    free(a);
    free(j);
    QString result(s);
    free(s);
    return result;
}

void UQQClient::loadContact() {
    qDebug() << "request contact list...";
    TEST(testLoadContact());

    QVariantMap param;
    QUrl url("http://s.web2.qq.com/api/get_user_friends2");

    param.insert("h", "hello");
    param.insert("hash", hashFriends(getLoginInfo("uin").toString().toLatin1().data(), getLoginInfo("ptwebqq").toString().toLatin1().data()));
    param.insert("vfwebqq", getLoginInfo("vfwebqq"));
    QJsonDocument doc;
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson();

    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, LoadContactAction);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));
}

void UQQClient::parseContact(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setContactData(m.value("result").toMap());
        qDebug() << "contact list ready.";
        getOnlineBuddies();
    } else {
        qDebug() << "parseContact:" << data;
    }
}

void UQQClient::testGetOnlineBuddies() {
    QFile file("test/status.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseOnlineBuddies(data);
}

void UQQClient::getOnlineBuddies() {
    qDebug() << "request online buddies...";
    TEST(testGetOnlineBuddies());

    QUrl url("http://d.web2.qq.com/channel/get_online_buddies2");
    QUrlQuery query;
    query.addQueryItem("clientid", getLoginInfo("clientid").toString());
    query.addQueryItem("psessionid", getLoginInfo("psessionid").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    qDebug() << url.toString();

    //QString url = QString("http://d.web2.qq.com/channel/get_online_buddies2?clientid=%1&psessionid=%2&t=%3")
    //        .arg(getLoginInfo("clientid").toString(),
    //             getLoginInfo("psessionid").toString(),
    //             getTimestamp());

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, GetOnlineBuddiesAction);
    request.setUrl(url);
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
        qDebug() << "request online buddies done.";
        loadGroups();
    } else {
        qDebug() << "parseOnlineBuddies:" << data;
    }
}

void UQQClient::testLoadGroups() {
    QFile file("test/group.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseGroups(data);
}

void UQQClient::loadGroups() {
    qDebug() << "request group list...";
    TEST(testLoadGroups());

    QUrl url("http://s.web2.qq.com/api/get_group_name_list_mask2");

    QVariantMap param;
    QJsonDocument doc;
    QNetworkRequest request;
    param.insert("vfwebqq", getLoginInfo("vfwebqq"));
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson();

    request.setAttribute(QNetworkRequest::User, LoadGroupsAction);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));
}

void UQQClient::parseGroups(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_group->setGroupData(m.value("result").toMap());
        qDebug() << "request group list done.";
        qDebug() << "ALL needed datas are loaded, show the main page...";
        emit ready();
    } else {
        qDebug() << "parseGroups:" << data;
    }
}

void UQQClient::testLoadGroupInfo(quint64 gid) {
    QFile file("test/groupinfo02.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseGroupInfo(gid, data);
}

void UQQClient::loadGroupInfo(quint64 gid) {
    qDebug() << "request group info..." << gid;
    TEST(testLoadGroupInfo(gid));

    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    if (!group) return;

    QUrl url("http://s.web2.qq.com/api/get_group_info_ext2");
    QUrlQuery query;
    query.addQueryItem("gcode", QString::number(group->code()));
    query.addQueryItem("vfwebqq", getLoginInfo("vfwebqq").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    qDebug() << url.toString();

    //QString url = QString("http://s.web2.qq.com/api/get_group_info_ext2?gcode=%1&vfwebqq=%2&t=%3")
    //        .arg(QString::number(gcode),
    //             getLoginInfo("vfwebqq").toString(),
    //             getTimestamp());

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, LoadGroupInfoAction);
    request.setAttribute(QNetworkRequest::UserMax, gid);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->get(request);
}

void UQQClient::parseGroupInfo(quint64 gid, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_group->setGroupDetail(gid, m.value("result").toMap(), m_contact);
        emit groupReady(gid);

        qDebug() << "request group" << gid << "info done.";

        UQQCategory *group = m_group->getGroupById(gid);
        Q_CHECK_PTR(group);
        if (!group) return;
        getGroupAccount(QString::number(group->code()));
    } else {
        qDebug() << "parseGroupInfo:" << data;
    }
    //qDebug() << "parseGroupInfo:" << data;
}

QString UQQClient::buddyMessageData(QString dstUin, QString content) {
    QVariantMap m;
    UQQMember *user = m_contact->member(getLoginInfo("uin").toString());
    Q_CHECK_PTR(user);
/*
    QString p = QString("{\"to\":%1,\"face\":%2,\"content\":\"[\\\"%3\\\",[\\\"font\\\",{\\\"name\\\":\\\"Arial\\\",\\\"size\\\":\\\"10\\\",\\\"style\\\":[0,0,0],\\\"color\\\":\\\"000000\\\"}]]\",\"msg_id\":%4,\"clientid\":\"%5\",\"psessionid\":\"%6\"}");
    p = p.arg(dstUin, QString::number(user->detail()->faceid()), content,
              QString::number(getRandomInt(10000000)), getLoginInfo("clientid").toString(),
              getLoginInfo("psessionid").toString());
    return p;
*/
    qDebug() << dstUin.toLongLong();
    m.insert("to", dstUin);
    m.insert("face", user->detail()->faceid());

    QVariantList contents;
    contents.append(content);

    QVariantList font;
    font.append("font");
    QVariantMap fontObject;
    fontObject.insert("name", "宋体");
    fontObject.insert("size", "10");
    fontObject.insert("color", "000000");

    QVariantList style;
    style.append(0);
    style.append(0);
    style.append(0);
    fontObject.insert("style", style); // style: bold,italic,underline
    font.append(fontObject);

    contents.append(font);

    m.insert("content", contents);
    m.insert("msg_id", QString::number(getRandomInt(10000000)));
    m.insert("clientid", getLoginInfo("clientid").toString());
    m.insert("psessionid", getLoginInfo("psessionid"));

    QJsonObject obj = QJsonObject::fromVariantMap(m);
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

QString UQQClient::groupMessageData(QString groupUin, QString content) {
    QVariantMap m;

    QString p = QString("{\"group_uin\":%1,\"content\":\"[\\\"%2\\\",[\\\"font\\\",{\\\"name\\\":\\\"Arial\\\",\\\"size\\\":\\\"10\\\",\\\"style\\\":[0,0,0],\\\"color\\\":\\\"000000\\\"}]]\",\"msg_id\":%3,\"clientid\":\"%4\",\"psessionid\":\"%5\"}");
    p = p.arg(groupUin,
              content,
              QString::number(getRandomInt(100000000)),
              getLoginInfo("clientid").toString(),
              getLoginInfo("psessionid").toString());
    return p;
}

void UQQClient::testSendBuddyMessage(QString dstUin, const QString &content) {
    QString p = "r=" + buddyMessageData(dstUin, content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    QString fromUin = getLoginInfo("uin").toString();
    UQQMember *member = m_contact->member(dstUin);
    Q_CHECK_PTR(member);
    UQQMessage *message = new UQQMessage(member);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(dstUin);
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());

    UQQMember *user = m_contact->member(fromUin);
    Q_CHECK_PTR(user);
    message->setName(user->nickname());
    member->addMessage(message);
}

/*
r={
    "to":123456,
    "face":123,
    "content":"["hello",["font",{"name":"Arial","size":"10","style":[0,0,0],"color":"000000"}]]",
    "msg_id":123456,
    "clientid":"123456",
    "psessionid":"..."
  }&clientid=123456&psessionid=....
*/
void UQQClient::sendBuddyMessage(QString dstUin, QString content) {
    TEST(testSendBuddyMessage(dstUin, content));

    QUrl url("http://d.web2.qq.com/channel/send_buddy_msg2");
    QString p = "r=" + buddyMessageData(dstUin, content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, SendBuddyMessageAction);
    request.setAttribute(QNetworkRequest::UserMax, dstUin);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));

    QString fromUin = getLoginInfo("uin").toString();
    UQQMember *member = m_contact->member(dstUin);
    Q_CHECK_PTR(member);
    UQQMessage *message = new UQQMessage(member);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(dstUin);
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());

    UQQMember *user = m_contact->member(fromUin);
    Q_CHECK_PTR(user);
    message->setName(user->nickname());
    member->addMessage(message);
}

void UQQClient::parseMessage(const QString &uin, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    int retcode = m.value("retcode", DefaultError).toInt();
    if (retcode == NoError) {
        qDebug() << QTime::currentTime().toString("hh:mm:ss") << "send to" << uin << "ok";
    } else {
        qWarning() << "parseMessage:" << data;
    }
}

void UQQClient::testSendGroupMessage(quint64 gid, const QString &content) {
    QString p = "r=" + groupMessageData(QString::number(gid), content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    QString fromUin = getLoginInfo("uin").toString();
    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    if (!group) return;
    UQQMessage *message = new UQQMessage(group);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(QString::number(gid));
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());
    group->addMessage(message);
}

void UQQClient::sendGroupMessage(quint64 gid, QString content) {
    qDebug() << QTime::currentTime().toString("hh:mm:ss") << "send group message...";
    TEST(testSendGroupMessage(gid, content));

    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    if (!group) return;

    QUrl url("http://d.web2.qq.com/channel/send_qun_msg2");
    QString p = "r=" + groupMessageData(QString::number(gid), content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, SendGroupMessageAction);
    request.setAttribute(QNetworkRequest::UserMax, gid);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));

    QString fromUin = getLoginInfo("uin").toString();

    UQQMessage *message = new UQQMessage(group);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(QString::number(gid));
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());

    group->addMessage(message);
}

void UQQClient::testGetGroupSig(quint64 gid, const QString &dstUin) {
    QFile file("test/group_sig.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    parseGroupSig(gid, dstUin, data);
}

void UQQClient::getGroupSig(quint64 gid, QString dstUin) {
    qDebug() << "request group sig...";
    TEST(testGetGroupSig(gid, dstUin));

    QUrl url("http://d.web2.qq.com/channel/get_c2cmsg_sig2");
    QUrlQuery query;
    query.addQueryItem("id", QString::number(gid));
    query.addQueryItem("to_uin", dstUin);
    query.addQueryItem("service_type", QString::number(0));
    query.addQueryItem("clientid", getLoginInfo("clientid").toString());
    query.addQueryItem("psessionid", getLoginInfo("psessionid").toString());
    query.addQueryItem("t", getTimestamp());
    url.setQuery(query);
    qDebug() << url.toString();

//    QString url = QString("http://d.web2.qq.com/channel/get_c2cmsg_sig2?id=%1&to_uin=%2&service_type=0&clientid=%3&psessionid=%4&t=%5")
//            .arg(QString::number(gid),
//                 dstUin,
//                 getLoginInfo("clientid").toString(),
//                 getLoginInfo("psessionid").toString(),
//                 getTimestamp());

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, GetGroupSigAction);
    request.setAttribute(QNetworkRequest::Attribute(QNetworkRequest::User + 1), gid);
    request.setAttribute(QNetworkRequest::UserMax, dstUin);
    request.setUrl(url);
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

void UQQClient::parseGroupSig(quint64 gid, const QString &dstUin, const QByteArray &data) {
    UQQMember *member = Q_NULLPTR;
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();
        member = this->member(gid, dstUin);
        Q_CHECK_PTR(member);
        if (member)
            member->setGroupSig(m.value("value").toString());
        qDebug() << "request group sig done.";
    } else {
        qDebug() << "parseGroupSig:" << data;
    }
}

QString UQQClient::sessionMessageData(quint64 gid, const QString &dstUin, const QString &content) {
    QVariantMap m;
    QString p = QString("{\"to\":%1,\"group_sig\":\"%2\",\"face\":%3,\"service_type\":0,\"content\":\"[\\\"%4\\\",[\\\"font\\\",{\\\"name\\\":\\\"Arial\\\",\\\"size\\\":\\\"10\\\",\\\"style\\\":[0,0,0],\\\"color\\\":\\\"000000\\\"}]]\",\"msg_id\":%5,\"clientid\":\"%6\",\"psessionid\":\"%7\"}");
    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    UQQMember *member = group->member(dstUin);
    Q_CHECK_PTR(member);
    UQQMember *user = m_contact->member(getLoginInfo("uin").toString());
    Q_CHECK_PTR(user);

    p = p.arg(dstUin,
              member->groupSig(),
              QString::number(user->detail()->faceid()),
              content,
              QString::number(getRandomInt(100000000)),
              getLoginInfo("clientid").toString(),
              getLoginInfo("psessionid").toString());
    return p;
}

void UQQClient::testSendSessionMessage(quint64 gid, QString dstUin, QString content) {
    QString p = "r=" + sessionMessageData(gid, dstUin, content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    QString fromUin = getLoginInfo("uin").toString();
    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    UQQMember *member = group->member(dstUin);
    Q_CHECK_PTR(member);

    UQQMessage *message = new UQQMessage(member);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(dstUin);
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());

    UQQMember *user = group->member(fromUin);
    Q_CHECK_PTR(user);
    message->setName(user->markname() == "" ? user->nickname() : user->markname());
    member->addMessage(message);
}

void UQQClient::sendSessionMessage(quint64 gid, QString dstUin, QString content) {
    qDebug() << "send session message...";
    TEST(testSendSessionMessage(gid, dstUin, content));

    QString fromUin = getLoginInfo("uin").toString();
    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    if (!group) return;
    UQQMember *member = group->member(dstUin);
    Q_CHECK_PTR(member);
    if (!member) return;

    QUrl url("http://d.web2.qq.com/channel/send_sess_msg2");
    QString p = "r=" + sessionMessageData(gid, dstUin, content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    if (member->groupSig().isEmpty()) {
        qWarning() << "group sig is empty";
        return;
    }

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, SendSessionMessageAction);
    request.setAttribute(QNetworkRequest::Attribute(QNetworkRequest::User + 1), gid);
    request.setAttribute(QNetworkRequest::UserMax, dstUin);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));

    UQQMessage *message = new UQQMessage(member);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(dstUin);
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());

    member->addMessage(message);
}

void UQQClient::testPoll() {
    qDebug() << "test poll";
    QFile file("test/hello_msg.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    parsePoll(data);

    file.setFileName("test/groupmsg.txt");
    file.open(QIODevice::ReadOnly);
    data = file.readAll();
    file.close();
    parsePoll(data);

    file.setFileName("test/sess_msg.txt");
    file.open(QIODevice::ReadOnly);
    data = file.readAll();
    file.close();
    parsePoll(data);
/*
    file.setFileName("test/kick_msg.txt");
    file.open(QIODevice::ReadOnly);
    data = file.readAll();
    file.close();
    parsePoll(data);
    */
}

void UQQClient::poll() {
    qDebug() << QTime::currentTime().toString("hh:mm:ss") << "begin poll...";
    TEST(testPoll());

    QVariantMap param;
    QUrl url("http://d.web2.qq.com/channel/poll2");

    param.insert("clientid", getLoginInfo("clientid"));
    param.insert("psessionid", getLoginInfo("psessionid"));
    param.insert("key", 0);
    param.insert("ids", QVariantList());
    QJsonDocument doc;
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson() + QString("&clientid=%1&psessionid=%2")
            .arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString());

    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, PollMessageAction);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));
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
                pollStatusChanged(m);
            } else if (pollType == "message") {
                pollMemberMessage(m);
            } else if (pollType == "kick_message") {
                //qDebug() << data;
                pollKickMessage(m);
            } else if (pollType == "group_message") {
                pollGroupMessage(m);
            } else if (pollType == "sess_message") {
                //qDebug() << data;
                pollSessionMessage(m);
            } else if (pollType == "input_notify") {
                //qDebug() << data;
                pollInputNotify(m);
            } else {
                qWarning() << "Unknown poll type:" << pollType;
                qDebug() << data;
            }
        }
    } else if (retcode == PollNormalReturn) {
        //qDebug() << "poll normal return";
    } else if (retcode == PollOfflineError) {
        qDebug() << "Poll error:" << PollOfflineError;
    }
    else {
        qWarning() << "parsePoll:" << data;
    }
    qDebug() << QTime::currentTime().toString("hh:mm:ss") << "poll done.";
    emit pollReceived();
}

void UQQClient::pollStatusChanged(const QVariantMap &m) {
    UQQMember *member;
    QString uin = m.value("uin").toString();
    int status = UQQMember::statusIndex(m.value("status").toString());
    int clientType = m.value("client_type").toInt();

    member = m_contact->member(uin);
    Q_CHECK_PTR(member);
    int oldStatus = member->status();
    if (oldStatus != status || member->clientType() != clientType) {
        m_contact->setBuddyStatus(uin, status, clientType);
        if (oldStatus != status) {
            if (oldStatus == UQQMember::OfflineStatus)
                emit buddyOnline(uin);
            emit buddyStatusChanged(member->gid(), uin);
        }
    }
}

void UQQClient::pollInputNotify(const QVariantMap &m) {
    QString fromUin = m.value("from_uin").toString();
    UQQMember *member = m_contact->member(fromUin);
    Q_CHECK_PTR(member);
    if (member)
        member->setInputNotify(true);
}

void UQQClient::pollMemberMessage(const QVariantMap &m) {
    QString content;
    QString src = m.value("from_uin").toString();
    UQQMember *member = m_contact->member(src);
    Q_CHECK_PTR(member);
    UQQMessage *message = new UQQMessage(member);

    message->setId(m.value("msg_id").toInt());
    message->setId2(m.value("msg_id2").toInt());
    message->setType(m.value("msg_type").toInt());
    message->setSrc(src);
    message->setDst(m.value("to_uin").toString());

    QDateTime datetime =
            QDateTime::fromMSecsSinceEpoch(m.value("time").toLongLong() * 1000); // s -> ms
    message->setTime(datetime);

    QVariantList list = m.value("content").toList();
    QVariantList fontList = list.takeFirst().toList();

    for (int i = 0; i < list.size(); i++) {
        content.append(list.at(i).toString());
    }
    //qDebug() << "receive member message:" << content;
    message->setContent(content);
    message->setName(member->markname() == "" ? member->nickname() : member->nickname());
    member->addMessage(message);
    member->setInputNotify(false);

    emit memberMessageReceived(member->gid());
}

void UQQClient::pollGroupMessage(const QVariantMap &m) {
    QString content;
    quint64 gcode = m.value("group_code").toULongLong();
    UQQCategory *group = m_group->getGroupByCode(gcode);
    Q_CHECK_PTR(group);
    if (!group) return;

    UQQMessage *message = new UQQMessage(group);

    message->setId(m.value("msg_id").toInt());
    message->setId2(m.value("msg_id2").toInt());
    message->setType(m.value("msg_type").toInt());
    message->setSrc(m.value("send_uin").toString());
    message->setDst(m.value("to_uin").toString());

    QDateTime datetime =
            QDateTime::fromMSecsSinceEpoch(m.value("time").toLongLong() * 1000); // s -> ms
    message->setTime(datetime);

    QVariantList list = m.value("content").toList();
    QVariantList fontList = list.takeFirst().toList();

    for (int i = 0; i < list.size(); i++) {
        content.append(list.at(i).toString());
    }
    //qDebug() << "receive group message:" << content;
    message->setContent(content);
    group->addMessage(message);

    emit groupMessageReceived(group->id());
}

void UQQClient::pollSessionMessage(const QVariantMap &m) {
    QString content;
    QString fromUin = m.value("from_uin").toString();
    quint64 gid = m.value("id").toULongLong();
    UQQMember *member = Q_NULLPTR;

    UQQMessage *message = new UQQMessage();
    message->setId(m.value("msg_id").toInt());
    message->setId2(m.value("msg_id2").toInt());
    message->setType(m.value("msg_type").toInt());
    message->setSrc(fromUin);
    message->setDst(m.value("to_uin").toString());

    QDateTime datetime =
            QDateTime::fromMSecsSinceEpoch(m.value("time").toLongLong() * 1000); // s -> ms
    message->setTime(datetime);

    QVariantList list = m.value("content").toList();
    QVariantList fontList = list.takeFirst().toList();

    for (int i = 0; i < list.size(); i++) {
        content.append(list.at(i).toString());
    }
    message->setContent(content);

    if ((member = this->member(gid, fromUin)) != Q_NULLPTR) {
        member->addMessage(message);
        //emit sessionMessageReceived(group->id());
    } else {
        m_contact->addSessMessage(message);
        getStrangerInfo(gid, fromUin);
        emit memberMessageReceived(UQQCategory::StrangerCategoryId);
    }
}

// {"way":"poll","show_reason":1,"reason":"reason msg"}
void UQQClient::pollKickMessage(const QVariantMap &m) {
    qDebug() << "pollKickMessage";
    //bool showReason = m.value("show_reason").toBool();
    //if (showReason)
    //    addLoginInfo("errMsg", m.value("reason").toString());

    emit kicked(m.value("reason").toString());
}

QList<QObject *> UQQClient::getContactList() {
    QList<QObject *> categories;
    QList<UQQCategory *> &list = m_contact->categories();
    for (int i = 0; i < list.size(); i++) {
        categories.append(list.at(i));
    }
    return categories;
}

QList<QObject *> UQQClient::getGroupList() {
    QList<QObject *> groups;
    QList<UQQCategory *> &list = m_group->groups();
    for (int i = 0; i < list.size(); i++) {
        groups.append(list.at(i));
    }
    return groups;
}

QList<QObject *> UQQClient::getMember(QString uin) {
    QList<QObject *> members;
    UQQMember *member = Q_NULLPTR;
    member = m_contact->member(uin);
    Q_CHECK_PTR(member);
    members.append(member);

    return members;
}

QList<QObject *> UQQClient::getCategoryMembers(quint64 catid) {
    //qDebug() << "get category members...";
    QList<QObject *> list;
    const QList<UQQMember *> &members = m_contact->membersInCategory(catid, true);

    for (int i = 0; i < members.size(); i++) {
        list.append(members.at(i));
    }
    //qDebug() << "category members:" << list.size();
    return list;
}

QList<QObject *> UQQClient::getGroupMembers(quint64 gid) {
    QList<QObject *> list;
    const QList<UQQMember *> &members = m_group->memberInGroup(gid, true);

    for (int i = 0; i < members.size(); i++) {
        list.append(members.at(i));
    }
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

int     UQQClient::getRandomInt(int max) {
    qint64 ms = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    qsrand(ms);
    return qrand() % max;
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
