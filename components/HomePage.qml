import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {

    Repeater {
        id: repeater
        //anchors.fill: parent
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        model: QQ.Client.getMember(QQ.Client.getLoginInfo("uin"))

        Column {
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                margins: units.gu(1)
            }

            spacing: units.gu(1)

            MemberTitle {
                id: title
                width: parent.width

                icon: modelData.face == "" ? "../friend.png" : modelData.face
                markname: modelData.markname
                nickname: modelData.detail ? modelData.detail.nickname : ""
                longnick: modelData.longnick
                online: true
                status: modelData.status

                onClicked: {
                    if (detail.height == 0) {
                        detail.height = units.gu(23);
                        detail.opacity = 1;
                        lnickExpanded = true;
                    } else {
                        detail.height = 0;
                        detail.opacity = 0;
                        lnickExpanded = false;
                        longnickLineCount = 1;
                    }
                }

                onIconClicked: {
                    statusPopover.caller = title;
                    statusPopover.show();
                }

                StatusPopover {
                    id: statusPopover

                    onTriggered: {
                        QQ.Client.changeStatus(status);
                    }
                }
            }

            MemberDetail {
                id: detail
                anchors {
                    left: parent.left
                    right: parent.right
                }
                opacity: 0
                height: 0

                Behavior on height {
                    NumberAnimation {}
                }
                Behavior on opacity {
                    NumberAnimation {}
                }
            }
            ListItem.ThinDivider {}
        }
    }
}
