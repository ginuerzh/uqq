#include "uqqclient.h"
#include "uqqmemberdetail.h"


//#define __TST

#ifdef __TST
#define TEST(func) \
    func; return;
#else
#define TEST(func)
#endif


UQQClient::UQQClient(QObject *parent)
    : QObject(parent) {

    m_manager = new QNetworkAccessManager(this);
    m_contact = new UQQContact(this);
    m_group = new UQQGroup(this);

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
        parseAccount(p.toString(), data, GetMemberAccountAction);
        break;
    case GetGroupAccountAction:
        parseAccount(p.toString(), data, GetGroupAccountAction);
        break;
    case GetLongNickAction:
        parseLongNick(p.toString(), data);
        break;
    case GetMemberLevelAction:
        parseMemberLevel(p.toString(), data);
        break;
    case GetMemberInfoAction:
        parseMemberInfo(p.toString(), data);
        break;
    case GetUserFaceAction:
        saveFace(p.toString(), data);
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
        parseSendMessage(p.toString(), data);
        break;
    case SendGroupMessageAction:
        parseSendMessage(p.toString(), data);
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
     * this doesn't work :(, the package will be sent twice, I don't know why???
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

void UQQClient::logout() {
    QString url = QString("GET /channel/logout2?ids=&clientid=%1&psessionid=%2&t=%3")
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
    //~ for test
    TEST(testLogin(pwd, vc, status))

    QString url = QString("http://ptlogin2.qq.com/login?u=%1&p=%2&verifycode=%3&aid=%4")
            .arg(uin, pwd, vc, getLoginInfo("aid").toString()) +
             "&webqq_type=10&remember_uin=0&login2qq=1&u1=http%3A%2F%2Fweb.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&h=1&ptredirect=0&ptlang=2052&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=2-6-22950&mibao_css=m_webqq&t=1&g=1";

    addLoginInfo("uin", uin);
    addLoginInfo("vc", vc);
    addLoginInfo("pwd", pwd);
    addLoginInfo("status", status);

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
    addLoginInfo("ptwebqq", ptwebqq);
    QString data = QString("r={\"status\":\"%1\",\"ptwebqq\":\"%2\",\"passwd_sig\":\"\",\"clientid\":\"%3\",\"psessionid\":null}"
            "&clientid=%4&psessionid=null")
            .arg(getLoginInfo("status").toString(),
                 ptwebqq,
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
        addLoginInfo("status", m.value("status").toString());

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

    UQQMember *user = new UQQMember(UQQCategory::IllegalCategoryId, uin, m_contact);
    user->setAccount(uin);
    qDebug() << "login status:" << status;
    user->setStatus(UQQMember::statusIndex(status));
    m_contact->addMember(user);

    getUserFace();
    getMemberDetail(uin);

    emit loginSuccess();
}

void UQQClient::getMemberDetail(QString uin) {
    getMemberAccount(uin);
    getMemberLevel(uin);
    getMemberInfo(uin);
}

void UQQClient::testGetAccount(const QString &uin, Action action) {
    QFile file("test/account.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    if (action == GetMemberAccountAction)
        parseAccount(uin, data, action);
}

void UQQClient::getMemberAccount(const QString &uin) {
    getAccount(uin, GetMemberAccountAction);
}

void UQQClient::getGroupAccount(const QString &uin) {
    getAccount(uin, GetGroupAccountAction);
}

void UQQClient::getAccount(const QString &uin, Action action) {
    TEST(testGetAccount(uin, action))

    QString url = QString("http://s.web2.qq.com/api/get_friend_uin2?tuin=%1&verifysession=&type=4&code=&vfwebqq=%2&t=%3")
            .arg(uin, getLoginInfo("vfwebqq").toString(), getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, action);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->get(request);
}

/*
 *{"retcode":0,"result":{"uiuin":"","account":123456,"uin":12345668}}
 */
void UQQClient::parseAccount(const QString &uin, const QByteArray &data, Action action) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m = m.value("result").toMap();

        if (action == GetMemberAccountAction) {
            UQQMember *member = m_contact->member(uin);
            Q_CHECK_PTR(member);
            member->setAccount(m.value("account").toString());
        } else {
            UQQCategory *group = m_group->getGroupByCode(uin.toULongLong());
            Q_CHECK_PTR(group);
            group->setAccount(m.value("account").toULongLong());
        }
    } else {
        qDebug() << "parseAccount:" << data;
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
    TEST(testGetLongNick(uin))

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
    UQQMember *member = Q_NULLPTR;
    if (m.value("retcode", DefaultError).toInt() == NoError &&
            (list = m.value("result").toList()).size() > 0) {
        m = list.at(0).toMap();
        member = m_contact->member(uin);
        Q_CHECK_PTR(member);
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
    TEST(testGetMemberLevel(uin))

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
        Q_CHECK_PTR(member);
        member->setLevel(m.value("level").toInt());
        member->setLevelDays(m.value("days").toInt());
        member->setLevelHours(m.value("hours").toInt());
        member->setLevelRemainDays(m.value("remainDays").toInt());
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
    // for test
    TEST(testGetMemberInfo(uin))

    QString url = QString("http://s.web2.qq.com/api/get_friend_info2?tuin=%1&vfwebqq=%2&t=%3")
            .arg(uin, getLoginInfo("vfwebqq").toString(), getTimestamp());
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, GetMemberInfoAction);
    request.setAttribute(QNetworkRequest::UserMax, uin);
    request.setUrl(QUrl(url));
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
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setMemberDetail(uin, m.value("result").toMap());
    } else {
        qDebug() << "parseMemberInfo:" << data;
    }
}

void UQQClient::getUserFace() {
    getFace(getLoginInfo("uin").toString(), 1);
}

void UQQClient::getMemberFace(QString uin) {
    getFace(uin);
}

void UQQClient::testGetFace(const QString &uin) {
    QString path = "../friend.png";
    m_contact->member(uin)->setFace(path);

    getLongNick(uin);
}

void UQQClient::getFace(const QString &uin, int cache, int type) {
    TEST(testGetFace(uin))

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
    UQQMember *member = Q_NULLPTR;
    //QString account = m_contact->member(uin)->account();
    Q_ASSERT(account.length() > 0);
    QString path = facePath + "/" + uin + imageFormat(data);

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(data);
    file.close();

    member = m_contact->member(uin);
    Q_CHECK_PTR(member);
    member->setFace(path);

    getLongNick(uin);
}

void UQQClient::testChangeStatus(const QString &status) {
    QString uin = getLoginInfo("uin").toString();
    UQQMember *user = m_contact->member(uin);
    if (user)
        user->setStatus(UQQMember::statusIndex(status));
}

void UQQClient::changeStatus(QString status) {
    TEST(testChangeStatus(status))

    QString url = QString("http://d.web2.qq.com/channel/change_status2?newstatus=%1&clientid=%2&psessionid=%3&t=%4")
            .arg(status,
                 getLoginInfo("clientid").toString(),
                 getLoginInfo("psessionid").toString(),
                 getTimestamp());
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
        qDebug() << "change status ok";
        QString uin = getLoginInfo("uin").toString();
        UQQMember *user = m_contact->member(uin);
        if (user)
            user->setStatus(UQQMember::statusIndex(status));

    } else {
        qWarning() << "parseChangeStatus:" << data;
    }
}

// get friends' face images in the category index
void UQQClient::loadInfoInCategory(int category) {
    const QList<UQQMember *> &members = m_contact->membersInCategory(category);
    for (int i = 0; i < members.size(); i++) {
        getMemberFace((members.at(i))->uin());
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
    int alen= strlen(uin);
    int *c = (int *)malloc(sizeof(int)*strlen(uin));
    int d,b,k,clen;
    int elen=strlen(ptwebqq);
    char* e = ptwebqq;
    int h;
    int i;
    for(d=0;d<alen;d++){
        c[d]=uin[d]-'0';
    }
    //qDebug() << uin << ptwebqq;
    clen = d;
    for(b=0,k=-1,d=0;d<clen;d++){
        b += c[d];
        b %= elen;
        int f = 0;
        if(b+4>elen){
            int g;
            for(g=4+b-elen,h=0;h<4;h++)
                f |= h<g?((e[b+h]&255)<<(3-h)*8):((e[h-g]&255)<<(3-h)*8);
        }else{
            for(h=0;h<4;h++)
                f |= (e[b+h]&255)<<(3-h)*8;
        }
        k ^= f;
    }
    memset(c,0,sizeof(int)*alen);
    c[0] = k >> 24&255;
    c[1] = k >> 16&255;
    c[2] = k >> 8&255;
    c[3] = k & 255;
    char* ch = QString("0123456789ABCDEF").toLatin1().data();
    char* ret = (char *)malloc(10);
    memset(ret,0,10);
    for(b=0,i=0;b<4;b++){
        ret[i++]=ch[c[b]>>4&15];
        ret[i++]=ch[c[b]&15];
    }
    QString result(ret);
    //qDebug() << "result" << ret;
    free(c);
    free(ret);
    return result;
}

void UQQClient::loadContact() {
    //~ for test
    TEST(testLoadContact())

    QVariantMap param;
    QString url = QString("http://s.web2.qq.com/api/get_user_friends2");

    param.insert("h", "hello");
    param.insert("hash", hashFriends(getLoginInfo("uin").toString().toLatin1().data(), getLoginInfo("ptwebqq").toString().toLatin1().data()));
    param.insert("vfwebqq", getLoginInfo("vfwebqq"));
    QJsonDocument doc;
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson();

    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, LoadContactAction);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->post(request, QUrl::toPercentEncoding(p, "="));
}

void UQQClient::parseContact(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_contact->setContactData(m.value("result").toMap());

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
    TEST(testLoadGroups())

    QString url = QString("http://s.web2.qq.com/api/get_group_name_list_mask2");
    QVariantMap param;
    QJsonDocument doc;
    QNetworkRequest request;

    param.insert("vfwebqq", getLoginInfo("vfwebqq"));
    doc.setObject(QJsonObject::fromVariantMap(param));
    QString p = "r=" + doc.toJson();

    request.setAttribute(QNetworkRequest::User, LoadGroupsAction);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->post(request, QUrl::toPercentEncoding(p, "="));
}

void UQQClient::parseGroups(const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();
    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_group->setGroupData(m.value("result").toMap());
        emit contactReady();
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
    TEST(testLoadGroupInfo(gid))

    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    quint32 gcode = group->code();
    QString url = QString("http://s.web2.qq.com/api/get_group_info_ext2?gcode=%1&vfwebqq=%2&t=%3")
            .arg(QString::number(gcode),
                 getLoginInfo("vfwebqq").toString(),
                 getTimestamp());

    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::User, LoadGroupInfoAction);
    request.setAttribute(QNetworkRequest::UserMax, gid);
    request.setUrl(QUrl(url));
    request.setRawHeader("Referer", "http://s.web2.qq.com/proxy.html?v=20110412001&callback=1&id=1");
    m_manager->get(request);
}

void UQQClient::parseGroupInfo(quint64 gid, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    if (m.value("retcode", DefaultError).toInt() == NoError) {
        m_group->setGroupInfo(gid, m.value("result").toMap());
        emit groupReady(gid);

        UQQCategory *group = m_group->getGroupById(gid);
        Q_CHECK_PTR(group);
        getGroupAccount(QString::number(group->code()));
    } else {
        qDebug() << "parseGroupInfo:" << data;
    }
}

QString UQQClient::buddyMessageData(QString dstUin, QString content) {
    QVariantMap m;
    UQQMember *user = m_contact->member(getLoginInfo("uin").toString());
    Q_CHECK_PTR(user);

    QString p = QString("{\"to\":%1,\"face\":%2,\"content\":\"[\\\"%3\\\",[\\\"font\\\",{\\\"name\\\":\\\"Arial\\\",\\\"size\\\":\\\"10\\\",\\\"style\\\":[0,0,0],\\\"color\\\":\\\"000000\\\"}]]\",\"msg_id\":%4,\"clientid\":\"%5\",\"psessionid\":\"%6\"}");
    p = p.arg(dstUin, QString::number(user->detail()->faceid()), content,
              QString::number(getRandomInt(10000000)), getLoginInfo("clientid").toString(),
              getLoginInfo("psessionid").toString());
    return p;

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

    QString p = QString("{\"group_uin\":%1,\"content\":\"[\\\"%3\\\",[\\\"font\\\",{\\\"name\\\":\\\"Arial\\\",\\\"size\\\":\\\"10\\\",\\\"style\\\":[0,0,0],\\\"color\\\":\\\"000000\\\"}]]\",\"msg_id\":%4,\"clientid\":\"%5\",\"psessionid\":\"%6\"}");
    p = p.arg(groupUin,
              content,
              QString::number(getRandomInt(100000000)),
              getLoginInfo("clientid").toString(),
              getLoginInfo("psessionid").toString());
    return p;
}

void UQQClient::testSendBuddyMessage(QString dstUin, QString content) {
    QString p = "r=" + buddyMessageData(dstUin, content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));
    //qDebug() << p;
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
    message->setName(user->detail()->nickname());
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
    // for test
    TEST(testSendBuddyMessage(dstUin, content))

    QString url = QString("http://d.web2.qq.com/channel/send_buddy_msg2");
    QString p = "r=" + buddyMessageData(dstUin, content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    //qDebug() << p;
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, SendBuddyMessageAction);
    request.setAttribute(QNetworkRequest::UserMax, dstUin);
    request.setUrl(QUrl(url));
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
    message->setName(user->detail()->nickname());
    member->addMessage(message);
}

void UQQClient::parseSendMessage(const QString &uin, const QByteArray &data) {
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QVariantMap m = obj.toVariantMap();

    int retcode = m.value("retcode", DefaultError).toInt();
    if (retcode == NoError) {
        qDebug() << "send to" << uin << "ok";
    } else {
        qWarning() << "parseSendMessage:" << data;
    }
}

void UQQClient::testSendGroupMessage(quint64 gid, QString content) {
    QString p = "r=" + groupMessageData(QString::number(gid), content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));
    //qDebug() << p;

    QString fromUin = getLoginInfo("uin").toString();
    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    UQQMessage *message = new UQQMessage(group);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(QString::number(gid));
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());
    group->addMessage(message);
}

void UQQClient::sendGroupMessage(quint64 gid, QString content) {
    TEST(testSendGroupMessage(gid, content))

    QString url = QString("http://d.web2.qq.com/channel/send_qun_msg2");
    QString p = "r=" + groupMessageData(QString::number(gid), content);
    p.append(QString("&clientid=%1&psessionid=%2").arg(getLoginInfo("clientid").toString(), getLoginInfo("psessionid").toString()));

    //qDebug() << p;
    QNetworkRequest request;

    request.setAttribute(QNetworkRequest::User, SendGroupMessageAction);
    request.setAttribute(QNetworkRequest::UserMax, gid);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
    m_manager->post(request, QUrl::toPercentEncoding(p, "=&"));

    QString fromUin = getLoginInfo("uin").toString();
    UQQCategory *group = m_group->getGroupById(gid);
    Q_CHECK_PTR(group);
    UQQMessage *message = new UQQMessage(group);
    message->setType(TYPE_SEND);
    message->setSrc(fromUin);
    message->setDst(QString::number(gid));
    message->setContent(content);
    message->setTime(QDateTime::currentDateTime());

    group->addMessage(message);
}

void UQQClient::testPoll() {
    qDebug() << "test poll";
    QFile file("test/groupmsg.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    parsePoll(data);
}

void UQQClient::poll() {
    // for test
    TEST(testPoll())

    QVariantMap param;
    QString url = QString("http://d.web2.qq.com/channel/poll2");

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
    request.setUrl(QUrl(url));
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
                pollKickMessage(m);
            } else if (pollType == "group_message") {
                pollGroupMessage(m);
            } else if (pollType == "input_notify") {
                qDebug() << data;
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
        qWarning() << "parsePoll:" << data;
    }

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
            emit buddyStatusChanged(member->category(), uin);
        }
    }
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

    emit memberMessageReceived(member->category());
}

void UQQClient::pollGroupMessage(const QVariantMap &m) {
    QString content;
    quint64 gcode = m.value("group_code").toULongLong();
    UQQCategory *group = m_group->getGroupByCode(gcode);
    Q_CHECK_PTR(group);

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

void UQQClient::pollKickMessage(const QVariantMap &m) {
    qDebug() << "pollKickMessage:" << m;
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
    qDebug() << "group list" << groups.size();
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
    QList<QObject *> list;
    const QList<UQQMember *> &members = m_contact->membersInCategory(catid, true);

    for (int i = 0; i < members.size(); i++) {
        list.append(members.at(i));
    }
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
