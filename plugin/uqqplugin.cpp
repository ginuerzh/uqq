#include "uqqplugin.h"
#include "httpclient.h"

#include <QtQml>

void UQQPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("UQQ"));
    // @uri UQQ
    qmlRegisterType<HttpClient>(uri, 1, 0, "HttpClient");
}
