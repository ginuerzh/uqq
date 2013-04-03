import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Rectangle {
    id: member
    width: parent.width
    height: info.height + units.gu(2)
    clip: true
    color: "mintcream"

    Rectangle {
        id:background
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: title.height + units.gu(2)

        color: "whitesmoke"
    }

    Column {
        id: wrapper
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: units.gu(1)
        }
        spacing: units.gu(1)

        Item {
            id: title
            width: parent.width
            height: info.height

            UbuntuShape {
                id: face
                width: units.gu(5)
                height: width
                anchors.left: parent.left

                image: Image {
                    source: model.modelData.face == "" ? "../friend.png" : model.modelData.face
                }
                opacity: model.modelData.status < 5 ? 1.0 : 0.3

                MouseArea {
                    anchors.fill: parent
                    anchors.margins: -units.gu(1)
                    onClicked: {
                        //console.log("face clicked");
                        if (member.state != "Message")
                            member.state = "Message"
                        else
                            member.state = ""
                    }
                }
            }
            Column {
                id: info
                anchors {
                    left: face.right
                    right: parent.right
                    leftMargin: units.gu(0.5)
                }
                spacing: units.gu(1)

                Row {
                    Label {
                        text: model.modelData.markname == "" ? model.modelData.nickname : model.modelData.markname
                    }
                    Label {
                        id: nickname
                        opacity: 0
                        text: model.modelData.markname == "" ? "" : "(" + model.modelData.nickname + ")"
                    }
                }
                Label {
                    width: parent.width
                    text: model.modelData.longnick
                    wrapMode: Text.Wrap
                    elide: Text.ElideRight
                    maximumLineCount: 3
                }
            }

            MouseArea {
                anchors {
                    fill: parent
                    leftMargin: face.width + units.gu(1)
                    rightMargin: -units.gu(1)
                    topMargin: -units.gu(1)
                    bottomMargin: -units.gu(1)
                }
                onClicked: {
                    if (member.state == "") {
                        member.state = "Detail"
                    }
                    else
                        member.state = ""
                }
            }
        }

        Loader {
            id: detailLoader

            property var modelData: model.modelData

            width: parent.width
            height: units.gu(23)
            source: "Detail.qml"
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
                height: wrapper.height + units.gu(2)
            }
            PropertyChanges {
                target: detailLoader
                opacity: 1
            }
            PropertyChanges {
                target: member
                color: "white"
            }
            PropertyChanges {
                target: background
                color: "aliceblue"
            }
            PropertyChanges {
                target: nickname
                opacity: 1
            }
        },
        State {
            name: "Message"

            PropertyChanges {
                target: member.ListView.view
                explicit: true
                contentY: member.y
                interactive: false
            }
            PropertyChanges {
                target: member
                height: member.ListView.view.height
            }
            PropertyChanges {
                target: member
                color: "white"
            }
            PropertyChanges {
                target: background
                color: "aliceblue"
            }
            PropertyChanges {
                target: nickname
                opacity: 1
            }
        }

    ]

    transitions: [
        Transition {
            from: ""
            to: "Detail"
            SequentialAnimation {
                PropertyAction { target: detailLoader; property: "active"; value: true }
                ParallelAnimation {
                    NumberAnimation { properties: "height,opacity" }
                    ColorAnimation { }
                }
                ScriptAction { script: QQ.Client.getMemberDetail(model.modelData.uin); }
            }
        },
        Transition {
            from: "Detail"
            to: ""
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { properties: "height,opacity" }
                    ColorAnimation {}
                }
                PropertyAction { target: detailLoader; property: "active"; value: false }
            }
        },
        Transition {
            from: "Message"
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { properties: "contentY,height,opacity" }
                    ColorAnimation {}
                }
            }
        },
        Transition {
            to: "Message"
            SequentialAnimation {
                ParallelAnimation {
                    NumberAnimation { properties: "contentY,height,opacity" }
                    ColorAnimation {}
                }
                PropertyAction { target: detailLoader; property: "active"; value: false }
            }
        }
    ]
}

