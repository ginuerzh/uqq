import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Item {
    id: listDelegate
    width: parent.width
    height: titleBar.height
    //clip: true

    UbuntuShape {
        id: background
        anchors {
            fill: parent
            leftMargin: units.gu(0.2)
            rightMargin: units.gu(0.2)
            bottomMargin: units.gu(0.2)
        }
        color: "white"
        radius: "small"
        opacity: 0
    }

    ListItem.Subtitled {
        id: titleBar
        icon: Qt.resolvedUrl("friend.png")
        text: nickname +
              (listDelegate.state != "" ? " (" + qq + ")" : "")
        subText: speech
        highlightWhenPressed: false

        onClicked: {
            listDelegate.ListView.view.currentIndex = index

            if (listDelegate.state == "")
                listDelegate.state = "DETAIL"
            else
                listDelegate.state = ""
        }
    }

    Button {
        id: talkButton
        height: titleBar.height
        width: height
        anchors {
            left: parent.left
            top: parent.top
            leftMargin: units.gu(1.5)
        }
        opacity: 0

        onClicked: {
            listDelegate.ListView.view.currentIndex = index
            listDelegate.state = "MESSAGE"
        }
    }

    Column {
        id: contents
        anchors {
            left: parent.left
            right: parent.right
            top: titleBar.bottom
            leftMargin: units.gu(2)
            rightMargin: units.gu(2)
            topMargin: units.gu(1)
            bottomMargin: units.gu(1)
        }
        height: 0
        spacing: units.gu(1)

        Grid {
            id: infoList
            opacity: 0
            columns: 2
            spacing: units.gu(1)

            Label { text: i18n.tr("性别: ") + "男" }
            Label { text: i18n.tr("生肖: ") + "虎" }
            Label { text: i18n.tr("星座: ") + "巨蟹座" }
            Label { text: i18n.tr("血型: ") + "A型" }
            Label { text: i18n.tr("生日: ") + "2013年1月1日" }
            Label { text: i18n.tr("国家/地区: ") + "中国" }
            Label { text: i18n.tr("省份: ") + "北京" }
            Label { text: i18n.tr("城市: ") + "北京市" }
            Label { text: i18n.tr("电话: ") + "0123456789" }
            Label { text: i18n.tr("手机: ") +"-" }
            Label { text: i18n.tr("邮箱: ") + "abc@gmail.com" }
            Label { text: i18n.tr("职业: ") + "程序员" }
            Label { text: i18n.tr("毕业院校: ") + "家里蹲大学" }
            Label { text: i18n.tr("个人主页: ") + "homepage.com" }
            Label { text: i18n.tr("个人说明: ") + "......" }
        }
/*
        TextArea {
            id: msgArea
            width: contents.width
            height: contents.height - titleBar.height - units.gu(3)
            opacity: 0
            //readOnly: true
            text: "fasdgsad\n
                    fasdfsd\n
                    fsadfsadf\n
                    fsffsf"
        }

        Row {
            id: sendRow
            opacity: 0
            spacing: units.gu(1)

            TextArea {
                id: sendArea
                height: contents.height - msgArea.height - units.gu(1)
                width: contents.width - height - units.gu(1)
                //opacity: 0

                text: "a very longgggggggggggggggggggggggggggggggggggggggggggggggggggg text"
            }
            Button {
                id: sendButton
                height: sendArea.height
                width: height
                color: "darkorange"
                text: i18n.tr("发送")
                onClicked: console.log("Send Message")
            }

        }
*/
    }

    states: [
        State {
            name: "DETAIL"

            PropertyChanges {
                target: contents
                height: infoList.height
            }
            PropertyChanges {
                target: listDelegate
                height: titleBar.height + contents.height + units.gu(3)
            }
            PropertyChanges {
                target: background
                opacity: 1
            }
            PropertyChanges {
                target: titleBar
                showDivider: false
            }
            PropertyChanges {
                target: infoList
                opacity: 1
            }
        },
        State {
            name: "MESSAGE"

            PropertyChanges {
                target: listDelegate.ListView.view
                interactive: false
                explicit: true
                contentY: listDelegate.y
            }
            PropertyChanges {
                target: listDelegate
                height: listDelegate.ListView.view.height
            }
            PropertyChanges {
                target: contents
                height: listDelegate.height - titleBar.height - units.gu(2)
            }
            PropertyChanges {
                target: background
                color: Qt.lighter("skyblue", 1.3)
                opacity: 1
            }
            PropertyChanges {
                target: titleBar
                showDivider: false
            }
            PropertyChanges {
                target: talkButton
                visible: false
            }
            PropertyChanges {
                target: infoList
                visible: false
            }

            PropertyChanges {
                target: msgArea
                opacity: 1
            }
            PropertyChanges {
                target: sendRow
                opacity: 1
            }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "height,contentY,opacity" }
        ColorAnimation {}
    }
}
