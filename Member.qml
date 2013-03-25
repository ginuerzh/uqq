import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: member
    height: title.height
    clip: true

    ListItem.Subtitled {
        id: title
        icon: model.modelData.face == "" ? Qt.resolvedUrl("friend.png") : Qt.resolvedUrl(model.modelData.face)
        text: model.modelData.markname == "" ? model.modelData.nickname : model.modelData.markname
        subText: model.modelData.longnick

        onClicked: {
            member.ListView.view.currentIndex = index
            if (member.state == "") {
                //console.log("expand")
                detailLoader.source = "UserDetail.qml"
                member.state = "Expand"
            } else {
                member.state = ""
                detailLoader.source = "";
            }
        }
    }

    Loader {
        id: detailLoader
        anchors {
            left: parent.left
            right: parent.right
            top: title.bottom
        }
        height: units.gu(25)
    }

    states: State {
        name: "Expand"
        PropertyChanges {
            target: member
            height: units.gu(20)
        }
    }

    transitions: [
        Transition {
            from: ""
            to: "Expand"
            SequentialAnimation {
                NumberAnimation { properties: "height,opacity" }
            }
        },
        Transition {
            from: "Expand"
            to: ""
            SequentialAnimation {
                NumberAnimation { properties: "height,opacity" }
            }
        }
    ]
}

