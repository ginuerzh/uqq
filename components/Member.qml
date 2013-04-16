import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Rectangle {
    id: member
    height: title.height + units.gu(2)
    clip: true
    color: "whitesmoke"

    Column {
        id: wrapper
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
            nickname: modelData.nickname
            longnick: modelData.longnick
            online: modelData.status !== 6
            showMessageCount: member.state != "Message" && modelData.messageCount > 0
            status: modelData.status
            isVip: modelData.isVip

            onClicked: {
                if (member.state == "") {
                    member.state = "Detail";
                } else {
                    member.state = "";
                }
            }

            onIconClicked: {
                if (member.state != "Message") {
                    member.state = "Message";
                    //title.lnickExpanded = true;
                } else {
                    member.state = "";
                    //title.lnickExpanded = false;
                }
            }
        }

        Loader {
            id: detailLoader

            property int minHeight: units.gu(5)
            property int maxHeihgt: units.gu(23)

            width: parent.width
            //height: maxHeihgt
            sourceComponent: MemberDetail {
                property bool expanded: false
                onClicked: {
                    if (msgLoader.active) {
                        if (expanded) {
                            detailLoader.height = detailLoader.minHeight;
                        } else {
                            detailLoader.height = detailLoader.maxHeihgt;
                        }
                        expanded = !expanded;
                    }
                }
            }

            Behavior on height {
                NumberAnimation {}
            }

            active: false
            opacity: 0
        }

        Loader {
            id: msgLoader
            width: parent.width
            height: member.ListView.view.height - title.height - detailLoader.height - parent.spacing * 4
            sourceComponent: Message {
                loadMsg: true
                onSendClicked: QQ.Client.sendBuddyMessage(modelData.uin, content);
            }

            active: false
            opacity: 0
        }
    }

    ListItem.ThinDivider { anchors.bottom: parent.bottom }

    states: [
        State {
            name: "Detail"

            PropertyChanges {
                target: detailLoader
                active: true
                height: maxHeihgt
                opacity: 1
            }
            PropertyChanges {
                target: member
                height: title.height + detailLoader.height + units.gu(2)
            }
            PropertyChanges {
                target: title
                showNickname: true
            }
            PropertyChanges {
                target: title
                lnickExpanded: true
            }
        },
        State {
            name: "Message"

            PropertyChanges {
                target: member
                height: member.ListView.view.height
            }
            PropertyChanges {
                target: member.ListView.view
                explicit: true
                contentY: member.y
                interactive: false
            }
            PropertyChanges {
                target: detailLoader
                height: minHeight
                active: true
                opacity: 1
            }
            PropertyChanges {
                target: msgLoader
                active: true
                opacity: 1
            }
            PropertyChanges {
                target: title
                showNickname: true
            }
            PropertyChanges {
                target: title
                lnickExpanded: true
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "*"
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { properties: "contentY,height,opacity" }
                    ColorAnimation {}
                }
                ScriptAction {
                    script: if (modelData.detail == null)
                                QQ.Client.getMemberDetail(modelData.uin);
                }
            }
        },
        Transition {
            from: "*"
            to: ""
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { properties: "contentY,height,opacity" }
                    ColorAnimation {}
                }
                PropertyAction {
                    target: detailLoader
                    property: "active"
                    value: false
                }
                PropertyAction {
                    target: msgLoader
                    property: "active"
                    value: false
                }
                PropertyAction {
                    target: title
                    property: "longnickLineCount"
                    value: 1
                }
            }
        },
        Transition {
            from: "Detail"
            to: "Message"
            NumberAnimation { properties: "contentY,height,opacity" }
        }
    ]
}

