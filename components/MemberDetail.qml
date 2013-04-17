import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Item {
    id: detail

    signal clicked

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

    clip: true

    MouseArea {
        anchors.fill: parent
        onClicked: detail.clicked();
    }

    Column {
        anchors.fill: parent
        spacing: units.gu(0.5)

        Row {
            width: parent.width

            Field {
                width: parent.width / 2
                label: i18n.tr("QQ号码:")
                value: modelData.account
            }
            Field {
                label: i18n.tr("等级:")
                value: modelData.level
            }
        }

        Row {
            width: parent.width

            Field {
                width: parent.width / 4
                label: i18n.tr("性别:")
                value: modelData.detail ? gender[modelData.detail.gender] : gender[0]
            }
            Field {
                width: parent.width / 4
                label: i18n.tr("生肖:")
                value: modelData.detail ? shengxiao[modelData.detail.shengxiao] : shengxiao[0]
            }
            Field {
                width: parent.width / 4
                label: i18n.tr("星座:")
                value: modelData.detail ? constel[modelData.detail.constel] : constel[0]
            }
            Field {
                label: i18n.tr("   血型:")
                value: modelData.detail ? blood[modelData.detail.blood] : blood[0]
            }
        }

        Row {
            width: parent.width

            Field {
                width: parent.width / 2
                label: i18n.tr("生日:")
                value: modelData.detail ? Qt.formatDate(modelData.detail.birthday, "yyyy-MM-dd") : "-"
            }

            Field {
                label: i18n.tr("来自:")
                value: modelData.detail ?
                           modelData.detail.country + modelData.detail.province + modelData.detail.city :
                           "-"
            }
        }
        Row {
            width: parent.width

            Field {
                width: parent.width / 2
                label: i18n.tr("毕业院校:")
                value: modelData.detail ? modelData.detail.college : "-"
            }
            Field {
                label: i18n.tr("职业:")
                value: modelData.detail ? modelData.detail.occupation : "-"
            }
        }

        Row {
            width: parent.width

            Field {
                width: parent.width / 2
                label: i18n.tr("电话:")
                value: modelData.detail ? modelData.detail.phone : "-"
            }
            Field {
                label: i18n.tr("手机:")
                value: modelData.detail ? modelData.detail.mobile : "-"
            }
        }
        Field {
            label: i18n.tr("邮箱:")
            value: modelData.detail ? modelData.detail.email : "-"
        }
        Field {
            label: i18n.tr("个人主页:")
            value: modelData.detail ? modelData.detail.homepage : "-"
        }

        Row {
            width: parent.width
            spacing: units.gu(1)

            Label {id: personal; text: i18n.tr("个人说明:") }
            Label {
                width: parent.width - personal.width
                text: modelData.detail ? modelData.detail.personal : "-"
                elide: Text.ElideRight
                maximumLineCount: 2
                wrapMode: Text.Wrap
            }
        }
    }
}
