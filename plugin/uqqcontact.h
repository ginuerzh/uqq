#ifndef UQQCONTACT_H
#define UQQCONTACT_H

#include <QtQml>

class UQQContact : public QObject
{
    Q_OBJECT
public:
    explicit UQQContact(QObject *parent = 0);
    ~UQQContact();

    static QString mapToJson(const QVariantMap &map);
    static QString listToJson(const QVariantList &list);

    void setDataMap(const QVariantMap &map);
    void setOnlineBuddies(const QVariantList &list);
    QVariantList getCategoryFriends(int index);

private:
    void setFriends(const QVariantList &list);
    void setMarknames(const QVariantList &list);
    void setVipInfo(const QVariantList &list);
    void setInfo(const QVariantList &list);
    void setCategories(const QVariantList &list);
    void setCategoryFriends();

    bool addFriendInfo(const QString &uin,
                  const QString &key, const QVariant &value);
    bool addCategoryInfo(int index,
                  const QString &key, const QVariant &value) ;
    QVariant getCategoryInfo(int index, const QString &key);
    int category(const QString uin);
    QVariantList friendsInCategory(int index);

signals:
    void categoryReady(QString json);
    
public slots:

private:
    QVariantList m_categories;
    QHash<QString, QVariantMap> m_friends;
    QList<QVariantList> m_catefriends;
    QVariantList m_onlines;
};

#endif // UQQCONTACT_H
