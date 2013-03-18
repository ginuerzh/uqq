#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QtNetwork>


class HttpClient : public QObject {

    Q_OBJECT

    Q_ENUMS(KnownHeaders)
    Q_ENUMS(ReadyState)
    Q_ENUMS(Method)

    Q_PROPERTY(QUrl link READ link NOTIFY linkChanged)
    Q_PROPERTY(Method method READ method NOTIFY methodChanged)
    Q_PROPERTY(ReadyState readyState READ readyState NOTIFY readyStateChanged)
    Q_PROPERTY(QVariant statusCode READ statusCode)
    Q_PROPERTY(QVariant errorCode READ errorCode)
    Q_PROPERTY(QString errorString READ errorString)

public:
    enum Method {
        Get,
        Post
    };

    enum KnownHeaders {
        ContentTypeHeader,
        ContentLengthHeader,
        LocationHeader,
        LastModifiedHeader,
        CookieHeader,
        SetCookieHeader,
        ContentDispositionHeader,
        UserAgentHeader,
        ServerHeader
    };

    enum ReadyState {
        Uninitialized,
        Open,
        Send,
        Receiving,
        Loaded
    };

    HttpClient(QObject *parent = 0);
    ~HttpClient();

    QUrl link() const;
    void setLink(QUrl &link);

    Method method() const;
    void setMethod(Method method);

    ReadyState readyState() const;
    void setReadyState(ReadyState readyState);

    QVariant statusCode() const;
    void setStatusCode(QVariant code);

    QVariant errorCode() const;
    void setErrorCode(QVariant errorCode);

    QString errorString() const;
    void setErrorString(QString errorString);

private:
    void finished(QNetworkReply *reply);
    void listCookies(QUrl url);

signals:
    void linkChanged();
    void methodChanged();
    void readyStateChanged();
    void statusCodeChanged();
    void errorCodeChanged();

    void textFinished(QString text);

public slots:
    void open(Method method, QUrl link);
    void setRequestHeader(KnownHeaders header, const QVariant & value);
    QString getRequestHeader(QString &name);
    void send(QVariant body = QVariant(""));

    void onFinished(QNetworkReply *reply);
    void onError(QNetworkReply::NetworkError error);

    QString getCookie(QString name, QUrl url);
    bool setCookie(QString name, QString value);
    void setHeader(QString header, QString value);
    QString toPercentEncoding(QString input, QString exclude, QString include);

private:
    QUrl m_link;
    Method m_method;
    QVariant m_statusCode;
    QVariant m_errorCode;
    QString m_errorString;
    ReadyState m_readState;

    QVariantMap m_headers;
    QNetworkAccessManager *manager;
};

#endif // HTTPCLIENT_H
