import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {

    Repeater {
        id: repeater
        anchors.fill: parent
        model: QQ.Client.getMember(QQ.Client.getLoginInfo("uin"))

        Column {
            anchors {
                left: parent.left
                right: parent.right
                margins: units.gu(1)
            }

            spacing: units.gu(1)

            MemberTitle {
                width: parent.width

                icon: modelData.face == "" ? "../friend.png" : modelData.face
                markname: modelData.markname
                nickname: modelData.detail ? modelData.detail.nickname : ""
                longnick: modelData.longnick
                online: true
            }

            Detail {
                id: detail
                anchors {
                    left: parent.left
                    right: parent.right
                }
                height: units.gu(23)
            }
        }
    }
}
