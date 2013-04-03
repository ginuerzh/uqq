import QtQuick 2.0
import Ubuntu.Components 0.1

FocusScope {
    id: formInput
    property alias label: label.text
    property alias text: input.text
    property alias placeholderText: input.placeholderText
    property alias echoMode: input.echoMode
    property alias validator: input.validator

    width: childrenRect.width
    height: childrenRect.height

    Row {
        spacing: units.gu(2)

        Label {
            id: label
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: input
            focus: formInput.focus
        }
    }
}
