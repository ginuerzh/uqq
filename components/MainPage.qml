import QtQuick 2.0
import Ubuntu.Components 0.1
import UQQ 1.0 as QQ

MainView {
    objectName: "mainView"
    applicationName: "uqq"
    width: units.gu(45)
    height: units.gu(80)

    Timer {
        id: pollTimer
        interval: 63000     // trigger every 63s: 60s(max waiting time) + 3s(delay time)
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            QQ.Client.poll();
        }

        Component.onCompleted: {
            QQ.Client.pollReceived.connect(onPollReceived);
        }

        function onPollReceived() {
            pollTimer.restart();    // ok, start the next poll request immediately
        }
    }

    Tabs {
        id: tabs

        Tab {
            id: homePageTab
            objectName: "homePage"
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
        }
    }
}


