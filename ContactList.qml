import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Item {
    id: contactList
    anchors.fill: parent

    Column {
        width: parent.width
        height: childrenRect.height
        ListItem.Subtitled {
            icon: Qt.resolvedUrl("friend.png")
            text: "Gerry"
            subText: "subtitle"
            highlightWhenPressed: false
        }
    }
    ListView {
        id: listView
        anchors.fill: parent

        model: listModel
        delegate: ContactListDelegate {}
    }

}
