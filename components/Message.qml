import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: message

    ListModel {
        id: msgModel
    }

    state: showMsg ? "Message" : ""

    Column {
        anchors.fill: parent
        spacing: units.gu(1)

        Detail {
            id: detail
            width: parent.width
            height: units.gu(23)
        }

        UbuntuShape {
            color: "white"
            width: parent.width
            height: parent.height - detail.height - sendArea.height - units.gu(5)

            ListView {
                id: msgView
                anchors.fill: parent
                anchors.leftMargin: units.gu(1)
                anchors.rightMargin: units.gu(1)
                clip: true
                spacing: units.gu(3)

                model: msgModel

                delegate: Column {
                    anchors {
                        left: parent.left
                        right: parent.right
                    }

                    Label {
                        text: name + "  " + time
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
                    QQ.Client.sendMessage(modelData.uin, sendMsg.text);
                    msgModel.append(
                                {
                                    "name": "Gerry",
                                    "time": Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss"),
                                    "content": sendMsg.text
                                }
                               );
                    sendMsg.text = "";
                    msgView.positionViewAtEnd();
                }
            }
        }
    }

    function loadMessages() {
        var msgs = modelData.messages();
        for (var i = 0; i < msgs.length; i++) {
            msgModel.append(
                        {
                            "name": msgs[i].name,
                            "time": Qt.formatDateTime(msgs[i].time, "yyyy-MM-dd hh:mm:ss"),
                            "content": msgs[i].content
                        }
                        );
        }
        msgView.positionViewAtEnd()
    }

    function onMessageReceived() {
        //console.log("time:" + time + ", content:" + content)
        if (message.state == "Message") {
            loadMessages();
        }
    }

    states: [
        State {
            name: "Message"
            PropertyChanges {
                target: detail
                height: units.gu(7.5)
            }
        }
    ]
    transitions: [
        Transition {
            from: ""
            to: "Message"
            SequentialAnimation {
                NumberAnimation {
                    properties: "height"
                }
                ScriptAction {
                    script: {
                        loadMessages();
                        modelData.messageReceived.connect(onMessageReceived);
                    }
                }
            }
        },
        Transition {
            from: "Message"
            to: ""
            NumberAnimation {
                properties: "height"
            }
            ScriptAction {
                script: {
                    modelData.messageReceived.disconnect(onMessageReceived);
                }
            }
        }
    ]
}
