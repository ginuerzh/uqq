import QtQuick 2.0
import Ubuntu.Components 0.1

Flow {
    id: contentFlow
    width: parent.width
    property string textContent

    Component.onCompleted: {
        var pattern = /\[face\d{1,3}\]/;
        var index;

        while (textContent.length > 0) {
            index = textContent.search(pattern);
            if (index < 0) {
                textComponent.createObject(contentFlow, {text: textContent});
                textContent = "";
            } else {
                if (index > 0) {
                    textComponent.createObject(contentFlow, {text: textContent.substring(0, index)});
                    textContent = textContent.substring(index);
                }
                var end = textContent.indexOf("]");
                var face = textContent.substring(1, end);
                faceComponent.createObject(contentFlow, {source: getFace(face.substring(4))});

                textContent = textContent.substring(end + 1);
            }
        }
    }

    Component {
        id: faceComponent
        AnimatedImage {
            asynchronous: true
        }
    }
    Component {
        id: textComponent
        Label {
            property int maxWidth: parent.width
            wrapMode: Text.Wrap
            width:Math.min(maxWidth, paintedWidth)
        }
    }
}
