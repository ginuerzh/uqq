import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import Ubuntu.Components.Popups 0.1 as Popups
import UQQ 1.0 as QQ

Popups.Popover {
    id: groupSetting
    signal groupMaskChecked(bool notify, bool block)

    property int messageMask

    //Component.onCompleted: console.log("messageMask: " + messageMask);

    Column{
        width: parent.width

        ListItem.Standard {
            text: i18n.tr("群消息声音提示")

            control: CheckBox {
                id: notifyCheck
                anchors.verticalCenter: parent.verticalCenter
                checked: messageMask == QQ.Category.MessageNotify
                onClicked: {
                    groupSetting.groupMaskChecked(notifyCheck.checked, blockCheck.checked);
                }
            }
        }
        ListItem.Standard {
            text: i18n.tr("阻止本群消息")
            control: CheckBox {
                id: blockCheck
                anchors.verticalCenter: parent.verticalCenter
                checked: messageMask == QQ.Category.MessageBlocked
                onClicked: {
                    groupSetting.groupMaskChecked(notifyCheck.checked, blockCheck.checked);
                }
            }
        }
    }
}
