import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Column {
    Component.onCompleted: {
    }

    ListItem.Subtitled {
        id: title
        icon: Qt.resolvedUrl("../friend.png")
        highlightWhenPressed: false
    }
    /*
    Detail {
        id: detail
        anchors {
            left: parent.left
            right: parent.right
        }
        height: units.gu(25)
    }

    ListItem.ThinDivider {
    }*/
}

