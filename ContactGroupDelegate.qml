import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Item {
    id: groupDelegate

    property variant icon: titleBar.icon

    width: ListView.view.width
    height: titleBar.height

    ListItem.Standard {
        id: titleBar
        text: name + " [" + online + "/" + total + "]"
        selected: groupDelegate.state == "EXPANDING"

        Image {
            id: progressionArrow
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: units.gu(2)

            source: Qt.resolvedUrl("ListItemProgressionArrow.png")
        }

        onClicked: {
            //console.log("clicked, " + parent.height + ", " + groupDelegate.height)
            groupDelegate.ListView.view.currentIndex = index
            if (groupDelegate.state == "") {
                groupDelegate.state = "EXPANDING"
            } else
                groupDelegate.state = ""
        }
    }

    ContactList {
        id: contactList
        anchors {
            left: parent.left
            right: parent.right
            top: titleBar.bottom
        }
        height: groupDelegate.height - titleBar.height
        clip: true
        opacity: 0
    }

    states: State {
        name: "EXPANDING"

        PropertyChanges {
            target: groupDelegate.ListView.view.currentItem
            height: groupDelegate.ListView.view.height
        }
        PropertyChanges {
            target: groupDelegate.ListView.view
            interactive: false
        }
        PropertyChanges {
            target: groupDelegate.ListView.view
            explicit: true
            contentY: groupDelegate.y
        }
        PropertyChanges {
            target: progressionArrow
            rotation: 90
        }
        PropertyChanges {
            target: contactList
            opacity: 1
        }
    }
    transitions: Transition {
        NumberAnimation { properties: "height,contentY,rotation,opacity" }
    }
}
