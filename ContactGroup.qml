import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Item {
    id: contactGroup

    property alias model: groupView.model

    Column {
        anchors.fill: parent

        ListView {
            id: groupView
            width: parent.width
            height: parent.height
            delegate: ContactGroupDelegate{ }
        }
    }
}
