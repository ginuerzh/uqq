import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: contact

    Component.onCompleted: {
        QQ.Client.categoryReady.connect(onCategoryReady);
        QQ.Client.loadContact();
    }

    Flickable {
        id: flick
        anchors.fill: parent
        contentHeight: wrapper.height

        Column {
            id: wrapper
            width: parent.width

            Repeater {
                id: categories

                Category {
                    id: category
                    width: parent.width

                    onClicked: {
                        if (!category.loaded) {
                            //console.log("load friends in category " + index);
                            category.loaded = true;
                            category.model = QQ.Client.getCategoryMembers(index);
                            QQ.Client.loadInfoInCategory(index);
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

                    transitions: Transition {
                        NumberAnimation { properties: "height,contentY,rotation,opacity" }
                    }
                }
            }
        }
    }
    function onCategoryReady() {
        categories.model = QQ.Client.getCategories();
    }
}
