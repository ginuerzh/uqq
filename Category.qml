import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: category

    property alias model: memberView.model
    property bool loaded: false
    property alias rotation: arrow.rotation

    signal clicked()

    height: title.height

    ListItem.Standard {
        id: title
        text: modelData.name + " [" + modelData.online + "/" + modelData.total + "]"
        selected:  category.state != ""
        clip: true

        Image {
            id: arrow
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: units.gu(2)

            source: Qt.resolvedUrl("arrow.png")
        }
        onClicked: category.clicked()
    }
    ListView {
        id: memberView
        anchors {
            left: parent.left
            right: parent.right
            top: title.bottom
            bottom: parent.bottom
        }
        clip: true

        delegate: Member {
            id: member
            width: parent.width
        }
    }
}
