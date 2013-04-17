import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Item {
    id: detail

    property int minHeight: units.gu(8)
    property bool expanded: false

    height: expanded ? wrapper.height : minHeight
    //signal clicked

    clip: true

    MouseArea {
        anchors.fill: parent
        onClicked: expanded = !expanded
    }

    Column {
        id: wrapper
        width: parent.width
        spacing: units.gu(0.5)

        Row {
            width: parent.width

            Field {
                width: parent.width / 2
                label: i18n.tr("群号码:")
                value: modelData.account
            }
            Field {
                label: i18n.tr("等 级:")
                value: modelData.groupInfo ? modelData.groupInfo.level : "0"
            }
        }

        Row {
            width: parent.width

            Field {
                width: parent.width / 2
                label: i18n.tr("创建人:")
                value: modelData.groupInfo ? modelData.groupInfo.owner : "-"
            }

            Field {
                label: i18n.tr("创建时间:")
                value: modelData.groupInfo ? Qt.formatDate(modelData.groupInfo.createTime, "yyyy-MM-dd") : "-"
            }
        }

        Field {
            width: parent.width
            label: i18n.tr("分 类:")
            value: modelData.groupInfo ? modelData.groupInfo.gclass : "-"
        }

        Row {
            width: parent.width
            spacing: units.gu(1)
            Label {id: announce; text: i18n.tr("公 告:") }
            Label {
                width: parent.width - announce.width - parent.spacing
                text: modelData.groupInfo ? modelData.groupInfo.memo : "-"
                elide: Text.ElideRight
                wrapMode: Text.Wrap
            }
        }

        Row {
            width: parent.width
            spacing: units.gu(1)

            Label {id: intro; text: i18n.tr("简 介:") }
            Label {
                width: parent.width - intro.width - parent.spacing
                text: modelData.groupInfo ? modelData.groupInfo.fingerMemo : "-"
                elide: Text.ElideRight
                //maximumLineCount: 3
                wrapMode: Text.Wrap
            }
        }
    }

    Behavior on height {
        NumberAnimation {}
    }
}
