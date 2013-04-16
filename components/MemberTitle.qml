import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: title

    property var statusIcons: [
        "",
        "../res/status/Qme.png",
        "../res/status/busy.png",
        "../res/status/away.png",
        "../res/status/silent.png",
        "../res/status/hidden.png",
        ""
    ]

    property alias icon: faceImg.source
    property bool online: false
    property string markname
    property string nickname
    property string longnick
    property bool showMessageCount: false
    property bool showNickname: false
    property int status: 0
    property bool lnickExpanded: false
    property int longnickLineCount: 1
    property int minHeight: units.gu(5.5)
    property bool isVip: false

    signal iconClicked
    signal clicked
    clip: true

    height: minHeight

    onLnickExpandedChanged: {
        if (lnickExpanded) {
            longnickLineCount = 3;
            height = Qt.binding(function() { return info.height })
        } else {
            height = minHeight;
        }
    }

    Behavior on height {
        NumberAnimation {}
    }

    UbuntuShape {
        id: face
        width: units.gu(5)
        height: width
        anchors.left: parent.left

        image: Image {
            id: faceImg
        }
        opacity: online ? 1.0 : 0.3

        Image {
            width: units.gu(1.3)
            height: width
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            source: title.status < title.statusIcons.length ? title.statusIcons[title.status] : ""
        }

        MouseArea {
            anchors.fill: parent
            anchors.margins: -units.gu(1)
            onClicked: iconClicked()
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
                text: markname == "" ? nickname : markname
                color: isVip ? "red" : nickLabel.color
            }
            Label {
                id: nickLabel
                opacity: showNickname ? 1 : 0
                text: markname == "" ? "" : "(" + nickname + ")"
                Behavior on opacity {
                    NumberAnimation {}
                }
            }
        }
        Label {
            width: parent.width
            text: longnick == "" ? " " : longnick
            wrapMode: Text.Wrap
            elide: Text.ElideRight
            maximumLineCount: longnickLineCount
        }
    }

    UbuntuShape {
        width: newMsgCount.width + units.gu(2)
        height: newMsgCount.height + units.gu(1)
        anchors {
            top: parent.top
            right: parent.right
        }
        color: "orangered"
        visible: showMessageCount


        Label {
            id: newMsgCount
            anchors.centerIn: parent
            text: model.modelData.messageCount
            color: "white"
            font.bold: true
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
        onClicked: title.clicked()
    }
}
