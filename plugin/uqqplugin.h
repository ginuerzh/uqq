#ifndef UQQPLUGIN_H
#define UQQPLUGIN_H

#include <QtQml/QQmlExtensionPlugin>

class UQQPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // UQQPLUGIN_H
