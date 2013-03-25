import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    Component.onCompleted: {
        QQ.Client.loadUserInfo();
    }

    ListItem.Subtitled {
        id: user
        icon: Qt.resolvedUrl("friend.png")
        iconFrame: false
        highlightWhenPressed: false
    }
    UserDetail {
        id: detail

        anchors {
            left: parent.left
            right: parent.right
            top: user.bottom
            leftMargin: units.gu(2.5)
            topMargin: units.gu(1)
        }
    }
    ListItem.ThinDivider {
        anchors.top: detail.bottom
        anchors.topMargin: units.gu(1)
    }

    QtObject {
        id: props

        property var shengxiao: [
            "-", "鼠", "牛", "虎", "兔", "龙", "蛇",
            "马", "羊", "猴", "鸡", "狗", "猪"
        ]
        property var blood: [
            "-", "A", "B", "O", "AB", "其它"
        ]
        property var constel: [
            "-", "水瓶座", "双鱼座", "白羊座", "金牛座", "双子座", "巨蟹座",
            "狮子座", "处女座", "天秤座", "天蝎座", "射手座", "摩羯座"
        ]
    }

    JSONListModel {
        id: userModel
        query: "$"
        onJsonChanged: {
            if (count > 0) {
                var info = model.get(0);

                user.text = info.nick;
                user.subText = info.lnick;
                homePageTab.title = info.nick;

                detail.uin = Number(info.uin).toString();
                detail.level = info.levels.level;
                detail.days = info.levels.days;
                detail.remainDays = info.levels.remainDays;
                detail.gender = (info.gender == "female" ? "女" : "男");
                detail.shengxiao = props.shengxiao[info.shengxiao];
                detail.blood = props.blood[info.blood];
                detail.birthday = info.birthday.year + "-" +
                        info.birthday.month + "-" +
                        info.birthday.day;
                detail.constel = props.constel[info.constel];
                detail.country = info.country;
                detail.province = info.province;
                detail.city = info.city;
                detail.phone = info.phone;
                detail.mobile = info.mobile;
                detail.college = info.college;
                detail.occupation = info.occupation;
                detail.email = info.email;
                detail.homepage = info.homepage;
                detail.description = info.personal;
            }
        }
    }
}

