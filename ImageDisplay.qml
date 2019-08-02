import QtQuick 2.0
import QtQuick.Controls 2.4

import ImagePainter 1.0

Rectangle {
    color: "black"
    ImagePainter{
        id: left
        anchors.fill: parent
        mirrored: true

        Connections{
            target: control
            onNewLeftImage: {
                left.image = image
            }
        }
    }
}
