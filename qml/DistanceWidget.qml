import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQml 2.12
import "BaseWidget"

Rectangle{
    id: distanceWidget

    border.width: 1
    border.color: "grey"
    radius: 5

    implicitHeight: 20
    implicitWidth: 20

    color: theme.colorBackGround2

    property string text

    Text {
        id: textDistance
        anchors.fill: parent
        text: distanceWidget.text

        horizontalAlignment : Text.AlignHCenter
        verticalAlignment : Text.AlignVCenter

        ColumnLayout {
            anchors.right: parent.right

            height: textInputEditText.height
            spacing: 0

            property int buttonWidth: 20
            property int buttonHeight: 20

            Button {
                text:"+"
                width: parent.buttonWidth
                onClicked: distanceManager.incrementDistanceByStep()

                Layout.fillHeight: true
                Layout.preferredWidth: 20
            }

            Button {
                text:"-"
                width: parent.buttonWidth
                onClicked: distanceManager.decrementDistanceByStep()

                Layout.fillHeight: true
                Layout.preferredWidth: 20
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            popup.width = distanceWidget.width;
            popup.open()
        }
        hoverEnabled: true

        onContainsMouseChanged: containsMouse ? parent.border.color = theme.colorHighlight : parent.border.color = theme.colorNoHighlight

        onWheel: {
            if (wheel.angleDelta.y > 0)
            {
                distanceManager.incrementDistanceByStep()
            } else {
                distanceManager.decrementDistanceByStep()
            }
        }
    }

    Popup{
        id: popup

        margins: 0
        padding: 5
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        clip: true

        property int defaultHeight: 200//contentItem.height//popup.contentHeight
        property int defaultWidth: distanceWidget.width

//        contentWidth: width; // flickable content width is its own width, scroll only vertically
        contentHeight: childrenRect.height

        onOpened: {
            textInputEditText.forceActiveFocus()
        }

        onAboutToHide: {
            if (distanceManager.validateDistance(textInputEditText.text))
            {
                distanceWidget.text = textInputEditText.text
            }
        }

        enter: Transition {
            ParallelAnimation{
                NumberAnimation { target: popup; property: "width"; from: 10; to: distanceWidget.width; duration: 1000; easing.type: Easing.OutBounce; easing.amplitude: 0.1}
                NumberAnimation { target: popup; property: "height";from: 0; to: popup.contentHeight; duration: 1000; easing.type: Easing.OutBounce; easing.amplitude: 0.1}
                NumberAnimation { target: popup; property: "opacity";from: 0; to: 1; duration: 1000; easing.type: Easing.OutBounce }
            }
        }

        exit: Transition {
            ParallelAnimation{
                NumberAnimation { target: popup; property: "width"; to: 10; from: distanceWidget.width; duration: 1000; easing.type: Easing.OutBounce; easing.amplitude: 0.1}
                NumberAnimation { target: popup; property: "height";to: 0; from: popup.contentHeight; duration: 1000; easing.type: Easing.OutBounce; easing.amplitude: 0.1}
                NumberAnimation { target: popup; property: "opacity";to: 0; from: 1; duration: 1000; easing.type: Easing.OutBounce }
            }
        }

        background:
            Rectangle{
            color: "cornflowerblue"
            radius: 5
        }

        contentItem: Item
        {
            id: dialogContent

            Column{
                id: column

                anchors.left: parent.left
                anchors.right: parent.right

                TextField {
                    id: textInputEditText
                    width: 50
                    text: distanceWidget.text

                    anchors.left: parent.left
                    anchors.right: parent.right

                    validator: RegExpValidator {
                        regExp: /([0-9]+) *[A-Za-z.]{,2}/
                    }

                    onEditingFinished: {
                        console.log(focus + "   " + popup.opened + "   ")

                        // We don't want to close de popup when the textfield lose the focus
                        if (focus != false && popup.opened)
                        {
                            popup.close()
                        }
                    }

                    placeholderText: "Enter a distance. (ex: 25 km)"

                    Button {
                        width: 20
                        height: 20
                        text: "X"

//                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right

                        background: Item {} // Allow to have en transparent background

                        onClicked: textInputEditText.text = "1 m"

                        onHoveredChanged: hovered ? contentItem.color = theme.colorHighlight : contentItem.color = "grey"
                    }
                }
            }
        }
    }
}


