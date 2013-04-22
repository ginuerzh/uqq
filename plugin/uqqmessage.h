#ifndef UQQMESSAGE_H
#define UQQMESSAGE_H

#include <QObject>
#include <QDateTime>

class UQQMessage : public QObject
{
    Q_OBJECT
public:
    enum MessageType {
        TypeSend = 0x1000
    };


    Q_PROPERTY(QString src READ src)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QDateTime time READ time)
    Q_PROPERTY(QString content READ content)
    Q_PROPERTY(int type READ type)

    explicit UQQMessage(QObject *parent = 0);

    int id() const;
    void setId(int id);
    int id2() const;
    void setId2(int id2);
    int type() const;
    void setType(int type);
    QString src() const;
    void setSrc(const QString &src);
    QString name() const;
    void setName(const QString &name);
    QString dst() const;
    void setDst(const QString &dst);
    QDateTime time() const;
    void setTime(const QDateTime &time);
    quint32 replyIP() const;
    void setReplyIP(quint32 replyIP);
    QString content() const;
    void setContent(const QString &content);

signals:
    
public slots:
    
private:
    int     m_id;
    int     m_id2;
    int     m_type;
    QString m_srcUin;
    QString m_dstUin;
    QString m_name;
    QDateTime m_time;
    quint32 m_replyIP;
    QString m_content;

    int m_fontSize;
    QString m_fontColor;
    QString m_fontName;
    bool    m_boldStyle;
    bool    m_italicStyle;
    bool    m_underlineStyle;
};

#endif // UQQMESSAGE_H
