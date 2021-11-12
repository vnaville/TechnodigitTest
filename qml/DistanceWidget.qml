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

    property alias distance: textDistance.text

    signal newDistanceValidated

    signal errorOccurred(string errorString)

    Connections {
        target: distanceManager
        onDistanceValidatedChanged: {
            textDistance.text = distanceManager.getValidatedDistance()
            newDistanceValidated()
        }

        onErrorOccurred: {
            errorOccurred(distanceManager.getLastErrorString())
        }
    }

    MouseArea {
        id: distanceWidgetMouseArea

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


    RowLayout {
        anchors.fill: parent

        Text {
            id: textDistance
            horizontalAlignment : Text.AlignHCenter
            verticalAlignment : Text.AlignVCenter

            text: "1 m"

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ColumnLayout {
            Layout.preferredWidth: 20

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

    // Allow to drag and drop text into the widget
    DropArea {
        anchors.fill: parent

        onEntered: dropHightlight.visible = true
        onExited: dropHightlight.visible = false

        onDropped:{
            distanceManager.validateDistance(drop.text)
            onExited: dropHightlight.visible = false
        }

        Rectangle {
            id: dropHightlight
            anchors.fill: parent
            color: theme.colorHighlight
            radius: 5
            opacity: 0.5
            visible: false
        }
    }

    Popup{
        id: popup

        margins: 0
        padding: 5
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        clip: true
        contentHeight: childrenRect.height

        onOpened: {
            textInputEditText.forceActiveFocus()
        }

        onAboutToHide: {
            if (distanceManager.validateDistance(textInputEditText.text))
            {
                distanceWidget.distance = distanceManager.getValidatedDistance()
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
                    text: distanceWidget.distance

                    anchors.left: parent.left
                    anchors.right: parent.right

                    validator: RegExpValidator {
                        regExp: /([0-9]+) *[A-Za-z.]{,2}/
                    }

                    onEditingFinished: {
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


