import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: contact

    Flickable {
        id: flick
        anchors.fill: parent
        contentHeight: wrapper.height

        Column {
            id: wrapper
            width: parent.width

            Repeater {
                id: categories

                model: QQ.Client.getCategories()

                Category {
                    id: category
                    width: parent.width
                    property bool loaded: false

                    model: QQ.Client.getCategoryMembers(modelData.catIndex);

                    onClicked: {
                        if (!loaded) {
                            loaded = true;
                            QQ.Client.loadInfoInCategory(modelData.catIndex);
                        }

                        if (category.state == "" && category.model.length > 0) {
                            category.state = "Expand"
                        } else {
                            category.state = ""
                        }
                    }
                    states: State {
                        name: "Expand"

                        PropertyChanges {
                            target: category
                            height: contact.height
                            rotation: 90
                        }
                        PropertyChanges {
                            target: flick
                            explicit: true
                            contentY: category.y
                            interactive: false
                        }
                    }

                    transitions: [
                        Transition {
                            NumberAnimation { properties: "height,contentY,rotation,opacity" }
                        }
                    ]
                }
            }
        }
    }
}
