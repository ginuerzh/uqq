#ifndef UQQCATEGORY_H
#define UQQCATEGORY_H

#include <QObject>
#include <QList>
#include "uqqmember.h"

class UQQCategory : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int online READ online WRITE setOnline NOTIFY onlineChanged)
    Q_PROPERTY(int total READ total WRITE setTotal NOTIFY totalChanged)
    Q_PROPERTY(int index READ index NOTIFY indexChanged)

    explicit UQQCategory(QObject *parent = 0);
    
    QString name() const;
    void setName(const QString &name);
    int online() const;
    void setOnline(int online);
    int total() const;
    void setTotal(int total);
    int index() const;
    void setIndex(int index);

    void setMembers(const QList<UQQMember *> &members);
    QList<UQQMember *> &getMembers();
    void addMember(UQQMember *member);

signals:
    void nameChanged();
    void onlineChanged();
    void totalChanged();
    void indexChanged();
    
public slots:

private:
    QString m_name;
    int m_online;
    int m_total;
    int m_index;

    QList<UQQMember *> m_members;
};

#endif // CATEGORY_H
