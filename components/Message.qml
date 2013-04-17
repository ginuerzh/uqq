import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: message

    property bool loadMsg: false

    signal sendClicked(string content)

    onLoadMsgChanged: {
        if (loadMsg) {
            loadMessages(modelData.messages());
            //modelData.messageReceived.connect(onMessageReceived);
        }
    }

    Connections {
        target: modelData
        onMessageReceived: {
            loadMessages(modelData.newMessages());
        }
    }

    ListModel {
        id: msgModel
    }

    Column {
        anchors.fill: parent
        spacing: units.gu(1)

        UbuntuShape {
            color: "white"
            width: parent.width
            height: parent.height - sendArea.height - parent.spacing

            ListView {
                id: msgView
                anchors.fill: parent
                anchors.leftMargin: units.gu(1)
                clip: true
                spacing: units.gu(2)

                model: msgModel

                delegate: Column {
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    spacing: units.gu(0.5)

                    Label {
                        text: name + "  " + time
                        color: isSend ? "blue" : "green"
                    }
                    Item {
                        width: parent.width
                        height: contentText.height + units.gu(1)
                        //color: "aquamarine"

                        Label {
                            id: contentText
                            anchors {
                                left: parent.left
                                right: parent.right
                                leftMargin: units.gu(1)
                            }
                            wrapMode: Text.Wrap
                            text: content
                        }
                    }
                }

                Scrollbar {
                    flickableItem: msgView
                }
            }
        }

        Row {
            id: sendArea
            width: parent.width
            spacing: units.gu(1)

            TextField {
                id: sendMsg
                width: parent.width - sendBtn.width - units.gu(1)
            }
            Button {
                id: sendBtn
                enabled: sendMsg.text.length > 0
                color: "orangered"
                text: i18n.tr("发送")

                onClicked: {
                    message.sendClicked(sendMsg.text);
                    sendMsg.text = "";
                }
            }
        }
    }

    Component.onCompleted: {
    }
    Component.onDestruction: {
        //modelData.messageReceived.disconnect(onMessageReceived);
    }

    function loadMessages(msgs) {
        for (var i = 0; i < msgs.length; i++) {
            msgModel.append(
                        {
                            "name": msgs[i].name,
                            "time": Qt.formatDateTime(msgs[i].time, "yyyy-MM-dd hh:mm:ss"),
                            "content": msgs[i].content,
                            "isSend": msgs[i].type === -1 ? true : false
                        }
                        );
        }
        msgView.positionViewAtEnd()
    }
}
