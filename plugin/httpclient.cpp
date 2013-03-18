#include "httpclient.h"

HttpClient::HttpClient(QObject *parent)
    : QObject(parent) {

    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, &QNetworkAccessManager::finished,
            this, &HttpClient::onFinished);
}

HttpClient::~HttpClient() {
    delete manager;
}

QUrl HttpClient::link() const {
    return m_link;
}
void HttpClient::setLink(QUrl &link) {
    if (m_link != link) {
        m_link = link;
        emit linkChanged();
    }
}

HttpClient::Method HttpClient::method() const {
    return m_method;
}
void HttpClient::setMethod(Method method) {
    if (method != m_method) {
        m_method = method;
        emit methodChanged();
    }
}

HttpClient::ReadyState HttpClient::readyState() const {
    return m_readState;
}
void HttpClient::setReadyState(ReadyState readyState) {
    if (readyState != m_readState) {
        m_readState = readyState;
        emit readyStateChanged();
    }
}

QVariant HttpClient::statusCode() const {
    return m_statusCode;
}
void HttpClient::setStatusCode(QVariant code) {
    if (m_statusCode != code) {
        m_statusCode = code;
        emit statusCodeChanged();
    }
}

QVariant HttpClient::errorCode() const {
    return m_errorCode;
}
void HttpClient::setErrorCode(QVariant errorCode) {
    if (errorCode != m_errorCode) {
        m_errorCode = errorCode;
        emit errorCodeChanged();
    }
}

QString HttpClient::errorString() const {
    return m_errorString;
}
void HttpClient::setErrorString(QString errorString) {
    m_errorString = errorString;
}

QString HttpClient::getCookie(QString name, QUrl url) {
    QList<QNetworkCookie> cookies = manager->cookieJar()->cookiesForUrl(url);

    for (int i = 0; i < cookies.size(); i++) {
        if (cookies.at(i).name() == name) {
            return QString(cookies.at(i).value());
        }
    }
    return "";
}

void HttpClient::listCookies(QUrl url) {
    QNetworkCookie cookie;
    QList<QNetworkCookie> cookies = manager->cookieJar()->cookiesForUrl(url);
    qDebug() <<"----- " << url << "-----";
    qDebug() << "cookie number: " << cookies.size();
    foreach (cookie, cookies) {
        qDebug() << "name:" << cookie.name() << ", value:" << cookie.value() \
                 <<", domain:" << cookie.domain() << ", path:" << cookie.path();
    }
}

bool HttpClient::setCookie(QString name, QString value) {
    QNetworkCookie cookie(name.toUtf8(), value.toUtf8());
    cookie.setDomain(".qq.com");
    cookie.setPath("/");
    return manager->cookieJar()->insertCookie(cookie);
}

void HttpClient::setHeader(QString header, QString value) {
    m_headers.insert(header, value);
}

QString HttpClient::toPercentEncoding(QString input, QString exclude, QString include) {
    //qDebug() << "exclude:" << exclude << ",include:" << include;
    return QString(QUrl::toPercentEncoding(input, exclude.toUtf8(), include.toUtf8()));
}

void HttpClient::open(Method method, QUrl link) {
    m_headers.clear();  // clear all the headers
    setMethod(method);
    setLink(link);
    setReadyState(Open);
}

void HttpClient::send(QVariant body) {
    //QNetworkReply *reply;
    QNetworkRequest request(m_link);

    QVariantMap::const_iterator iter = m_headers.constBegin();
    while (iter != m_headers.constEnd()) {
        request.setRawHeader(iter.key().toUtf8(), iter.value().toByteArray());
        iter++;
    }

    switch(m_method) {
    case Get:
        manager->get(request);
        break;
    case Post:
        manager->post(request, body.toByteArray());
    }
    setReadyState(Send);
}

void HttpClient::onFinished(QNetworkReply *reply) {

    setStatusCode(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute));

    if (reply->error() == QNetworkReply::NoError) {
        emit textFinished(QString(reply->readAll()));
    } else {
        setErrorCode(reply->error());
        setErrorString(reply->errorString());
    }

    setReadyState(Loaded);
    reply->deleteLater();
}

