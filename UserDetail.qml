import QtQuick 2.0
import Ubuntu.Components 0.1
import UQQ 1.0 as QQ

Column {
    id: detail

    property string uin: "-"
    property int level: 0
    property int days: 0
    property int remainDays: 0
    property string gender: "-"
    property string shengxiao: "-"
    property string blood: "-"
    property string birthday: "-"
    property string constel: "-"
    property string country: "-"
    property string province: "-"
    property string city: "-"
    property string phone: "-"
    property string mobile: "-"
    property string college: "-"
    property string occupation: "-"
    property string email: "-"
    property string homepage: "-"
    property string description: "-"

    spacing: units.gu(1)

    Row {
        spacing: units.gu(3)
        Field {
            id: uin
            label: i18n.tr("QQ号码:")
            value: detail.uin
        }
        Field {
            id: level
            label: i18n.tr("等级:")
            value: detail.level
        }
    }
    Row {
        spacing: units.gu(5)
        Field {
            id: days
            label: i18n.tr("活跃天数:")
            value: detail.days + i18n.tr("天")
        }
        Field {
            id: remainDays
            label: i18n.tr("距升级还有:")
            value: detail.remainDays + i18n.tr("天")
        }
    }

    Row {
        spacing: units.gu(6)

        Field {
            id: gender
            label: i18n.tr("性别:")
            value: detail.gender
        }
        Field {
            id: shengxiao
            label: i18n.tr("生肖:")
            value: detail.shengxiao
        }
        Field {
            id: blood
            label: i18n.tr("血型:")
            value: detail.blood
        }
    }
    Row {
        spacing: units.gu(5)

        Field {
            id: birthday
            label: i18n.tr("生日:")
            value: detail.birthday
        }
        Field {
            id: constel
            label: i18n.tr("星座:")
            value: detail.constel
        }
    }
    Row {
        spacing: units.gu(2)

        Field {
            id: country
            label: i18n.tr("国家/地区:")
            value: detail.country
        }
        Field {
            id: province
            label: i18n.tr("省份:")
            value: detail.province
        }
        Field {
            id: city
            label: i18n.tr("城市:")
            value: detail.city
        }
    }
    Row {
        spacing: units.gu(5)

        Field {
            id: phone
            label: i18n.tr("电话:")
            value: detail.phone
        }
        Field {
            id: mobile
            label: i18n.tr("手机:")
            value: detail.mobile
        }
    }
    Row {
        spacing: units.gu(2)
        Field {
            id: college
            label: i18n.tr("毕业院校:")
            value: detail.college
        }
        Field {
            id: occupation
            label: i18n.tr("职业:")
            value: detail.occupation
        }
    }
    Field {
        id: email
        label: i18n.tr("邮箱:")
        value: detail.email
    }
    Field {
        id: homepage
        label: i18n.tr("个人主页:")
        value: detail.homepage
    }
    Field {
        id: description
        label: i18n.tr("个人说明:")
        value: detail.description
    }
}
