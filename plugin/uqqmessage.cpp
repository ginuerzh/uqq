#include "uqqmessage.h"

UQQMessage::UQQMessage(QObject *parent) :
    QObject(parent)
{
    setId(0);
    setId2(0);
    setType(0);
    setReplyIP(0);
}

int UQQMessage::id() const {
    return m_id;
}
void UQQMessage::setId(int id) {
    m_id = id;
}

int UQQMessage::id2() const {
    return m_id2;
}
void UQQMessage::setId2(int id2) {
    m_id2 = id2;
}

int UQQMessage::type() const {
    return m_type;
}
void UQQMessage::setType(int type) {
    m_type = type;
}

QString UQQMessage::src() const {
    return m_srcUin;
}
void UQQMessage::setSrc(const QString &src) {
    m_srcUin = src;
}

QString UQQMessage::name() const {
    return m_name;
}
void UQQMessage::setName(const QString &name) {
    m_name = name;
}

QString UQQMessage::dst() const {
    return m_dstUin;
}
void UQQMessage::setDst(const QString &dst) {
    m_dstUin = dst;
}

QDateTime UQQMessage::time() const {
    return m_time;
}
void UQQMessage::setTime(const QDateTime &time) {
    m_time = time;
}

quint32 UQQMessage::replyIP() const {
    return m_replyIP;
}
void UQQMessage::setReplyIP(quint32 replyIP) {
    m_replyIP = replyIP;
}

QString UQQMessage::content() const {
    return m_content;
}
void UQQMessage::setContent(const QString &content) {
    m_content = content;
}
