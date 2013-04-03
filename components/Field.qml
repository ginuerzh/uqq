import QtQuick 2.0
import Ubuntu.Components 0.1

Row {
    property string label
    property string value
    clip: true
    spacing: units.gu(1)

    Label { text: parent.label }
    Label { text: parent.value }
}
