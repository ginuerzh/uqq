import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.Popups 0.1 as Popups
import UQQ 1.0 as QQ

/*!
    \brief MainView with Tabs element.
           First Tab has a single Label and
           second Tab has a single ToolbarAction.
*/

Item {
    id: main
    width: units.gu(45)
    height: units.gu(80)
    property string msg

    Loader {
        id: loader
        anchors.fill: parent
        focus: true
        source: "components/LoginForm.qml"
        //source: "components/MainPage.qml"
    }

    Connections {
        target: QQ.Client
        onLoginSuccess: QQ.Client.loadContact();
        onReady: loader.source = "components/MainPage.qml";
        onKicked: {
            loader.source = "";
            main.msg = reason;
            PopupUtils.open(dialog, loader);
        }
    }

    Component {
        id: dialog
        Popups.Dialog {
            id: dialogue
            title: i18n.tr("连接中断")
            text: main.msg
            Button {
                text: i18n.tr("自动登陆")
                color: "orangered"
                onClicked: {
                    QQ.Client.autoReLogin();
                    PopupUtils.close(dialogue);
                }
            }
            Button {
                text: i18n.tr("取 消")
                color: "orangered"
                onClicked: {
                    loader.source = "components/LoginForm.qml";
                    PopupUtils.close(dialogue)
                }
            }
        }
    }
}
