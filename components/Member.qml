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

            onClicked: {
                if (member.state == "") {
                    member.state = "Detail"
                }
                else
                    member.state = ""
            }

            onIconClicked: {
                if (member.state != "Message") {
                    member.state = "Message"
                }
                else
                    member.state = ""
            }
        }

        Loader {
            id: msgLoader

            property bool showMsg: false

            width: parent.width
            height: member.ListView.view.height - title.height
            source: "Message.qml"
            active: false
            opacity: 0
        }
    }

    ListItem.ThinDivider { anchors.bottom: parent.bottom }

    states: [
        State {
            name: "Detail"

            PropertyChanges {
                target: member
                height: title.height + units.gu(25)
            }
            PropertyChanges {
                target: title
                showNickname: true
            }
            PropertyChanges {
                target: msgLoader
                active: true
                opacity: 1
            }
        },
        State {
            name: "Message"
            extend: "Detail"

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
                target: msgLoader
                showMsg: true
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { properties: "contentY,height,opacity" }
                    ColorAnimation {}
                }
                ScriptAction { script: if (modelData.detail == null) QQ.Client.getMemberDetail(modelData.uin); }
            }
        },
        Transition {
            to: ""
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { properties: "contentY,height,opacity" }
                    ColorAnimation {}
                }
                PropertyAction { target: msgLoader; property: "active"; value: false }
            }
        },
        Transition {
            from: "Detail"
            to: "Message"
            NumberAnimation { properties: "contentY,height" }
        }
    ]
}

