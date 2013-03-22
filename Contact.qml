import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import UQQ 1.0 as QQ

Item {
    id: friend

    Component.onCompleted: {
        QQ.Client.categoryReady.connect(onCategoryReady);
        QQ.Client.loadContact();
    }

    JSONListModel {
        id: categoryModel
        onJsonChanged: {
            //console.log("categories:" + count);
            if (count > 0) {
                groupView.model = model;
            }
        }
    }

    Column {
        anchors.fill: parent

        ListView {
            id: groupView
            width: parent.width
            height: parent.height
            delegate: list
            clip: true
        }
    }

    function onCategoryReady(json) {
        categoryModel.json = json;
        //console.log(json);
    }

    Component {
        id: list
        Item {
            id: listView
            width: ListView.view.width
            height: titleBar.height

            //Component.onCompleted: console.log("width:" + width + ", height:" + height)

            ListItem.Standard {
                id: titleBar
                text: name + " [" + online + "/" + total + "]"
                clip: true

                Image {
                    id: progressionArrow
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: units.gu(2)

                    source: Qt.resolvedUrl("arrow.png")
                }

                onClicked: {
                    listView.ListView.view.currentIndex = index
                    if (listView.state == "") {
                        friendModel.json = QQ.Client.getFriendsInCategory(index);
                        listView.state = "Expand"
                    } else {
                        listView.state = ""
                        friendModel.json = ""
                    }
                }
            }

            ListView {
                id: friendView
                anchors {
                    left: parent.left
                    right: parent.right
                    top: titleBar.bottom
                    bottom: parent.bottom
                }
                delegate: friendDelegate
            }

            JSONListModel {
                id: friendModel
                onJsonChanged: {
                    if (count > 0) {
                        //console.log("friends count: " + count)
                        friendView.model = model;
                    }
                }
            }

            Component {
                id: friendDelegate

                ListItem.Subtitled {
                    icon: Qt.resolvedUrl("friend.png")
                    text: (markname ? markname : nick)// + " (" + uin + ")"
                    //subText: "subtitle"
                    clip: true
                    iconFrame: false
                    //highlightWhenPressed: false
                }
            }

            states: State {
                name: "Expand"

                PropertyChanges {
                    target: listView.ListView.view.currentItem
                    height: listView.ListView.view.height
                }
                PropertyChanges {
                    target: listView.ListView.view
                    interactive: false
                }
                PropertyChanges {
                    target: listView.ListView.view
                    explicit: true
                    contentY: listView.y
                }
                PropertyChanges {
                    target: progressionArrow
                    rotation: 90
                }
            }
            transitions: Transition {
                NumberAnimation { properties: "height,contentY,rotation,opacity" }
            }
        }
    }
}
