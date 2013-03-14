import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Item {
    id: contactList

    ListView {
        id: listView
        anchors.fill: parent

        model: listModel
        delegate: ContactListDelegate {}
    }

    ListModel {
        id: listModel
        ListElement { qq: 121830387; nickname: "张三"; speech: "今天天气不错" }
        ListElement { qq: 121830387; nickname: "李四"; speech: "sleepy....." }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
        ListElement { qq: 121830387; nickname: "001"; speech: "bad!" }
    }
}
