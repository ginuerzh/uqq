import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: root

    Flickable {
        id: flick
        anchors.fill: parent
        contentHeight: wrapper.height

        Column {
            id: wrapper
            width: parent.width

            Repeater {
                id: groups

                model: QQ.Client.getGroupList()

                Category {
                    id: group

                    property bool loaded: false


                    width: parent.width
                    maxHeight: root.height
                    title: modelData.markname == "" ? modelData.name : modelData.markname
                    subtitle: modelData.markname == "" ? "" : "(" + modelData.name + ")"
                    iconSource: "../group.png"
                    iconPageSource:"GroupMessage.qml"
                    isGroup: true


                    Connections {
                        target: QQ.Client
                        onGroupReady: {
                            if (gid === modelData.id) {
                                group.model = QQ.Client.getGroupMembers(gid);
                                group.loaded = true;
                            }
                        }
                        onGroupMessageReceived: {
                            if (gid == modelData.id && group.state == "")
                                    group.newMsg = true;
                        }
                    }

                    onClicked: {
                        if (!loaded) {
                            QQ.Client.loadGroupInfo(modelData.id);
                        }
                    }
                    onIconClicked: {
                        if (!loaded) {
                            QQ.Client.loadGroupInfo(modelData.id);
                        }
                    }
                }
            }
        }
    }
}
