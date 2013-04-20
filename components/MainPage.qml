import QtQuick 2.0
import Ubuntu.Components 0.1
import QtMultimedia 5.0
import UQQ 1.0 as QQ

MainView {
    objectName: "mainView"
    applicationName: "uqq"

    Timer {
        id: pollTimer
        interval: 63000     // trigger every 63s: 60s(max waiting time) + 3s(delay time)
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            //console.log("poll timer triggered");
            QQ.Client.poll();
        }
    }

    Audio {
        id: newMsgAudio
        source: "../res/sound/classic/msg.wav"
    }

    Audio {
        id: onlineAudio
        source: "../res/sound/classic/online.wav"
    }

    Connections {
        target: QQ.Client
        onMemberMessageReceived: newMsgAudio.play();
        onGroupMessageReceived: newMsgAudio.play();
        onSessionMessageReceived: newMsgAudio.play();
        onBuddyOnline: onlineAudio.play();
        onPollReceived: pollTimer.restart();
    }

    Tabs {
        id: tabs

        Tab {
            id: homePageTab
            objectName: "homePage"
            title: i18n.tr("QQMe")
            page: HomePage {
                anchors.fill: parent
                anchors.topMargin: units.gu(9.5)
            }
        }

        // Second tab begins here
        Tab {
            objectName: "contact"
            iconSource: "friend.png"
            title: i18n.tr("联系人")

            // Tab content begins here
            page: Contact {
                anchors.fill: parent
                anchors.topMargin: units.gu(9.5)
            }
        }

        Tab {
            objectName: "groups"
            iconSource: "group.png"
            title: i18n.tr("QQ群")

            page: Group {
                anchors.fill: parent
                anchors.topMargin: units.gu(9.5)
            }
        }
    }
}


