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

                    //model: QQ.Client.getCategoryMembers(index);

                    onClicked: {
                        if (!loaded) {
                            model = QQ.Client.getCategoryMembers(index);
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
                        }
                        PropertyChanges {
                            target: flick
                            interactive: false
                        }
                        PropertyChanges {
                            target: flick
                            explicit: true
                            contentY: category.y
                        }
                        PropertyChanges {
                            target: category
                            rotation: 90
                        }
                    }

                    transitions: [
                        Transition {
                            from: ""
                            to: "Expand"
                            SequentialAnimation {
                                NumberAnimation { properties: "height,contentY,rotation,opacity" }
                                //ScriptAction { script: QQ.Client.getOnlineBuddies(); }
                            }
                        },
                        Transition {
                            from: "Expand"
                            to: ""
                            NumberAnimation { properties: "height,contentY,rotation,opacity" }
                        }
                    ]
                }
            }
        }
    }
}
