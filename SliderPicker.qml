import QtQuick 2.0
import QtQuick.Controls 2.4

Row{
    property alias from: slider.from
    property alias to: slider.to
    property alias value: slider.value

    Slider{
        id: slider
        from: 1.0
        to: 180
        value: 120
    }
    Label{
        text: slider.value.toFixed(1)
        color: "white"

        anchors.verticalCenter: parent.verticalCenter

        MouseArea{
            anchors.fill: parent
            onClicked: {
                dialog.open()
            }

            Dialog {
                id: dialog
                parent: mainContent
                title: "Set value"
                x: 50
                y: 50
                height: 180
                width: 250

                standardButtons: Dialog.Ok | Dialog.Cancel

                TextField{
                    id: input

                    width: dialog.width - 25

                    validator: DoubleValidator{
                        bottom: slider.from
                        top: slider.to
                    }

                    onEditingFinished: {
                        dialog.accept()
                    }
                }

                onOpened: {
                    input.text = ""
                    input.forceActiveFocus()
                }

                onAccepted: {
                    slider.value = parseFloat( input.text )
                }

                onRejected: console.log("Cancel clicked")
            }
        }
    }

}
