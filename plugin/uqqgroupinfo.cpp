#include "uqqgroupinfo.h"

UQQGroupInfo::UQQGroupInfo(QObject *parent) :
    QObject(parent)
{
    m_faceid = 0;
    m_flag = 0;
    m_level = 0;
}

int UQQGroupInfo::faceid() const {
    return m_faceid;
}
void UQQGroupInfo::setFaceid(int faceid) {
    m_faceid = faceid;
}

QString UQQGroupInfo::memo() const {
    return m_memo;
}
void UQQGroupInfo::setMemo(const QString &memo) {
    if (m_memo != memo) {
        m_memo = memo;
        emit memoChanged();
    }
}

QString UQQGroupInfo::fingerMemo() const {
    return m_fingerMemo;
}
void UQQGroupInfo::setFingerMemo(const QString &fingerMemo) {
    if (m_fingerMemo != fingerMemo) {
        m_fingerMemo = fingerMemo;
        emit fingerMemoChanged();
    }
}

QString UQQGroupInfo::gclass() const {
    return m_class;
}
void UQQGroupInfo::setGclass(const QString &gclass) {
    if (m_class != gclass) {
        m_class = gclass;
        emit gclassChanged();
    }
}

QDateTime UQQGroupInfo::createTime() const {
    return m_createTime;
}
void UQQGroupInfo::setCreateTime(const QDateTime &creatTime) {
    if (m_createTime != creatTime) {
        m_createTime = creatTime;
        emit createTimeChanged();
    }
}

int UQQGroupInfo::flag() const {
    return m_flag;
}
void UQQGroupInfo::setFlag(int flag) {
    m_flag = flag;
}

int UQQGroupInfo::level() const {
    return m_level;
}
void UQQGroupInfo::setLevel(int level) {
    if (m_level != level) {
        m_level = level;
        emit levelChanged();
    }
}

QString UQQGroupInfo::owner() const {
    return m_ownerUin;
}
void UQQGroupInfo::setOwner(const QString &uin) {
    if (m_ownerUin != uin) {
        m_ownerUin = uin;
        emit ownerChanged();
    }
}
