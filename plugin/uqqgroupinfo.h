#ifndef UQQGROUPINFO_H
#define UQQGROUPINFO_H

#include <QtQml>

class UQQGroupInfo : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString memo READ memo NOTIFY memoChanged)
    Q_PROPERTY(QDateTime createTime READ createTime NOTIFY createTimeChanged())
    Q_PROPERTY(int level READ level NOTIFY levelChanged())
    Q_PROPERTY(QString owner READ owner NOTIFY ownerChanged)
    Q_PROPERTY(QString fingerMemo READ fingerMemo NOTIFY fingerMemoChanged)
    Q_PROPERTY(QString gclass READ gclass NOTIFY gclassChanged)

    explicit UQQGroupInfo(QObject *parent = 0);

    int faceid() const;
    void setFaceid(int faceid);
    QString memo() const;
    void setMemo(const QString &memo);
    QString fingerMemo() const;
    void setFingerMemo(const QString &fingerMemo);
    QString gclass() const;
    void setGclass(const QString &gclass);
    QDateTime createTime() const;
    void setCreateTime(const QDateTime &creatTime);
    int flag() const;
    void setFlag(int flag);
    int level() const;
    void setLevel(int level);
    QString owner() const;
    void setOwner(const QString &uin);
    
signals:
    void memoChanged();
    void createTimeChanged();
    void levelChanged();
    void ownerChanged();
    void fingerMemoChanged();
    void gclassChanged();

public slots:
    
private:
    int m_faceid;
    QString m_memo;
    QString m_class;
    QString m_fingerMemo;
    QDateTime m_createTime;
    int m_flag;
    int m_level;
    QString m_ownerUin;

};

#endif // UQQGROUPINFO_H
