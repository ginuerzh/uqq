import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Column {
    id: brief
    spacing: units.gu(0.5)

    property var gender: [
        "-", "男", "女"
    ]
    property var shengxiao: [
        "-", "鼠", "牛", "虎", "兔", "龙", "蛇",
        "马", "羊", "猴", "鸡", "狗", "猪"
    ]
    property var blood: [
        "-", "A", "B", "O", "AB", "其它"
    ]
    property var constel: [
        " - ", "水瓶座", "双鱼座", "白羊座", "金牛座", "双子座", "巨蟹座",
        "狮子座", "处女座", "天秤座", "天蝎座", "射手座", "摩羯座"
    ]
/*
    Component.onCompleted: {
        console.log("detail completed")
    }
    Component.onDestruction: {
        console.log("detail destruction")
    }
*/
    Row {
        width: parent.width

        Field {
            width: parent.width / 2
            label: i18n.tr("QQ号码:")
            value: model.modelData.account
        }
        Field {
            label: i18n.tr("等级")
            value: model.modelData.level + "级"
        }
    }

    Row {
        width: parent.width

        Field {
            width: parent.width / 4
            label: i18n.tr("性别:")
            value: gender[modelData.gender]
        }
        Field {
            width: parent.width / 4
            label: i18n.tr("生肖:")
            value: shengxiao[modelData.shengxiao]
        }
        Field {
            width: parent.width / 4
            label: i18n.tr("星座:")
            value: constel[modelData.constel]
        }
        Field {
            label: i18n.tr("   血型:")
            value: blood[modelData.blood]
        }
    }

    Row {
        width: parent.width

        Field {
            width: parent.width / 2
            label: i18n.tr("生日:")
            value: modelData.birthday == "" ? "1970-01-01" : modelData.birthday
        }

        Field {
            label: i18n.tr("来自")
            value: modelData.country + modelData.province + modelData.city
        }
    }
    Row {
        width: parent.width

        Field {
            width: parent.width / 2
            label: i18n.tr("毕业院校:")
            value: modelData.college
        }
        Field {
            label: i18n.tr("职业:")
            value: modelData.occupation
        }
    }

    Row {
        width: parent.width

        Field {
            width: parent.width / 2
            label: i18n.tr("电话:")
            value: modelData.phone
        }
        Field {
            label: i18n.tr("手机:")
            value: modelData.mobile
        }
    }
    Field {
        label: i18n.tr("邮箱:")
        value: modelData.email
    }
    Field {
        label: i18n.tr("个人主页:")
        value: modelData.homepage
    }

    Row {
        width: parent.width
        spacing: units.gu(1)

        Label {id: personal; text: i18n.tr("个人说明:") }
        Label {
            width: parent.width - personal.width
            text: modelData.personal
            elide: Text.ElideRight
            maximumLineCount: 2
            wrapMode: Text.Wrap
        }
    }
}
