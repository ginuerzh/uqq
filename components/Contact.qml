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

                model: QQ.Client.getContactList()

                Category {
                    id: category

                    property bool loaded: false

                    width: parent.width
                    maxHeight: contact.height
                    model: QQ.Client.getCategoryMembers(modelData.id);

                    title: modelData.name + " [" + modelData.online + "/" + modelData.total + "]"

                    Connections {
                        target: QQ.Client
                        onMemberMessageReceived: {
                            if (catid == modelData.id && category.state == "")
                                    category.newMsg = true;
                        }
                    }

                    onClicked: {
                        if (!loaded) {
                            loaded = true;
                            QQ.Client.loadInfoInCategory(modelData.id);
                        }
                    }
                }
            }
        }
    }
}
