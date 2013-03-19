#include "uqqplugin.h"
#include "uqqclient.h"

#include <QtQml>

static QObject* porviderCallback(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    UQQClient *client = new UQQClient;
    return client;
}

void UQQPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("UQQ"));
    // @uri UQQ
    //qmlRegisterType<HttpClient>(uri, 1, 0, "HttpClient");
    qmlRegisterSingletonType<UQQClient>(uri, 1, 0, "Client", porviderCallback);
}
