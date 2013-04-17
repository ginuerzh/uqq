#include "uqqplugin.h"
#include "uqqclient.h"
#include "uqqcontact.h"
#include "uqqmemberdetail.h"
#include "uqqgroupinfo.h"

#include <QtQml>

static QObject* clientPorviderCallback(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    UQQClient *client = new UQQClient();
    return client;
}

void UQQPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("UQQ"));
    // @uri UQQ
    qmlRegisterSingletonType<UQQClient>(uri, 1, 0, "Client", clientPorviderCallback);
    qmlRegisterType<UQQMember>(uri, 1, 0, "Member");
    qmlRegisterType<UQQMemberDetail>(uri, 1, 0, "MemberDetail");
    qmlRegisterType<UQQGroupInfo>(uri, 1, 0, "GroupInfo");
}
