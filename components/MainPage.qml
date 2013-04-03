import QtQuick 2.0
import Ubuntu.Components 0.1
import UQQ 1.0 as QQ

MainView {
    objectName: "mainView"
    applicationName: "uqq"
    width: units.gu(45)
    height: units.gu(80)

    Timer {
        interval: 6000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            QQ.Client.poll();
        }
    }

    Tabs {
        id: tabs

        Tab {
            id: homePageTab
            objectName: "mainPage"
            title: i18n.tr("QQ")
            page: HomePage {
                anchors.fill: parent
                anchors.topMargin: units.gu(9.5)
            }
        }

        // Second tab begins here
        Tab {
            objectName: "friends"
            iconSource: Qt.resolvedUrl("friend.png")
            title: i18n.tr("联系人")

            // Tab content begins here
            page: Contact {
                anchors.fill: parent
                anchors.topMargin: units.gu(9.5)
            }

            ListModel {
                id: contactModel
                ListElement { name: "在线好友"; online: 28; total: 28 }
                ListElement { name: "我的好友"; online: 4; total: 20 }
                ListElement { name: "朋友"; online: 0; total: 18 }
                ListElement { name: "同事"; online: 1; total: 22 }
                ListElement { name: "陌生人"; online: 0; total: 2 }
                ListElement { name: "黑名单"; online: 0; total: 0 }
            }
        }
 /*
        // Third tab begins here
        Tab {
            objectName: "group"
            iconSource: "group.png"
            title: i18n.tr("QQ群")
            page: ContactGroup {
                anchors.fill: parent
                model: groupModel
            }

            ListModel {
                id: groupModel
                ListElement { name: "QQ群01"; online: 28; total: 28 }
                ListElement { name: "QQ群02"; online: 4; total: 20 }
                ListElement { name: "QQ群03"; online: 0; total: 18 }
                ListElement { name: "QQ群04"; online: 1; total: 22 }
                ListElement { name: "QQ群05"; online: 0; total: 2 }
                ListElement { name: "QQ群06"; online: 0; total: 0 }
                ListElement { name: "QQ群07"; online: 0; total: 0 }
                ListElement { name: "QQ群08"; online: 0; total: 0 }
                ListElement { name: "QQ群09"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
                ListElement { name: "QQ群10"; online: 0; total: 0 }
            }
        }

        Tab {
            objectName: "History"

            title: i18n.tr("最近联系人")

            // Tab content begins here
            page: Page {
                Column {
                    anchors.centerIn: parent
                    Label {
                        text: i18n.tr("Swipe from right to left to change tab.")
                    }
                }
            }
        }
        */
    }
}


