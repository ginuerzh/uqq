import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import Ubuntu.Components.Popups 0.1 as Popups

Popups.Popover {
    id: facePopover

    signal selected(int faceid)

    property string faceDir: "../res/face/default/"
    property string faceSubfix: ".gif"
    property var facelist: [
        "14", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "0",
        "50", "51", "96", "53", "54", "73", "74", "75", "76", "77", "78", "55", "56", "57", "58",
        "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "97", "98", "99", "100", "101",
        "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "32", "113", "114", "115",
        "63", "64", "59", "33", "34", "116", "36", "37", "38", "91", "92", "93", "29", "117", "72",
        "45", "42", "39", "62", "46", "47", "71", "95", "118", "119", "120", "121", "122", "123", "124",
        "27", "21", "23", "25", "26", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134"
    ]

    autoClose: true

    Grid {
        columns: 10
        spacing: units.gu(0.5)

        Repeater {
            model: facelist
            delegate: Button {
                width: units.gu(4)
                height: units.gu(4)
                ItemStyle.class: "transparent-button"
                iconSource: faceDir + modelData + faceSubfix
                onClicked: selected(modelData);
            }
        }
    }
}
