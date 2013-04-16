import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import Ubuntu.Components.Popups 0.1 as Popups

Popups.ActionSelectionPopover {
    id: statusPopover

    property string status: "online"

    signal triggered(string status, string text, string source)

    actions: ActionList {
        Action {
            text: i18n.tr("在线")
            iconSource: Qt.resolvedUrl("../res/status/imonline.png")
            onTriggered: statusPopover.triggered("online", text, iconSource)
        }

        Action {
            text: i18n.tr("Q我")
            iconSource: Qt.resolvedUrl("../res/status/Qme.png")
            onTriggered: statusPopover.triggered("callme", text, iconSource)
        }
        Action {
            text: i18n.tr("离开")
            iconSource: Qt.resolvedUrl("../res/status/away.png")
            onTriggered: statusPopover.triggered("away", text, iconSource)
        }
        Action {
            text: i18n.tr("忙碌")
            iconSource: Qt.resolvedUrl("../res/status/busy.png")
            onTriggered: statusPopover.triggered("busy", text, iconSource)
        }
        Action {
            text: i18n.tr("勿扰")
            iconSource: Qt.resolvedUrl("../res/status/silent.png")
            onTriggered: statusPopover.triggered("silent", text, iconSource)
        }
        Action {
            text: i18n.tr("隐身")
            iconSource: Qt.resolvedUrl("../res/status/hidden.png")
            onTriggered: statusPopover.triggered("hidden", text, iconSource)
        }
    }
}
