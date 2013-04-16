import QtQuick 2.0
import UQQ 1.0 as QQ

Column {
    spacing: units.gu(1)

    GroupDetail {
        id: detail
        width: parent.width
    }
    Message {
        width: parent.width
        height: parent.height - detail.height - parent.spacing * 2
        loadMsg: modelData.groupReady
        onSendClicked: QQ.Client.sendGroupMessage(modelData.id, content);
    }
}
