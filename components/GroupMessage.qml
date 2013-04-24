import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.Popups 0.1 as Popups
import UQQ 1.0 as QQ

Column {
    spacing: units.gu(1)

    GroupDetail {
        id: detail
        width: parent.width

        Image {
            width: units.gu(3)
            height: units.gu(3)
            anchors {
                right: detail.right
                top: detail.top
            }
            source: "../setting.png"
            MouseArea {
                anchors.fill: parent
                anchors.margins: -units.gu(1)
                onClicked: {
                    Popups.PopupUtils.open(groupSettingPopover, parent);
                }
            }
            Component {
                id: groupSettingPopover
                GroupSettingPopover {
                    messageMask: modelData.messageMask
                    onGroupMaskChecked: {
                        var mask = 0;
                        //console.log("group mask checked: " + notify + ", " + block);
                        if (block) mask = QQ.Category.MessageBlocked;
                        else if (notify) mask = QQ.Category.MessageNotify;
                        else mask = QQ.Category.MessageNotNotify;

                        QQ.Client.setGroupMask(modelData.id, mask);
                    }
                }
            }
        }
    }

    Message {
        width: parent.width
        height: parent.height - detail.height - parent.spacing * 2
        loadMsg: modelData.groupReady
        onSendClicked: QQ.Client.sendGroupMessage(modelData.id, content);
    }
}
