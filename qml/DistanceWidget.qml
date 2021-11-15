import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQml 2.12
import DistanceManager 1.0
import "BaseWidget"

/*
Widget which allow to edit a distance.
A new distance entered must be validated in order to be changed, and must follow a specific format.
*/
Rectangle{
    id: distanceWidget
    implicitHeight: 20
    implicitWidth: 20

    border.width: 1
    border.color: "grey"
    radius: 5
    color: theme.colorBackGround2

    property alias distance: textDistance.text
    signal newDistanceValidated
    signal errorOccurred(string errorString)

    // C++ classe which will do the complexes tasks of this widget
    DistanceManager {
        id: distanceManager
    }

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
            textInputEditText.text = textDistance.text
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

    // Button used for incrementation and decrementation of distance
    RowLayout {
        anchors.fill: parent

        Text {
            id: textDistance

            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment : Text.AlignHCenter
            verticalAlignment : Text.AlignVCenter
            text: "1 m"
        }

        ColumnLayout {
            Layout.preferredWidth: 20

            height: textInputEditText.height
            spacing: 0

            property int buttonWidth: 20
            property int buttonHeight: 20

            Button {
                id: buttonIncrement

                Layout.fillHeight: true
                Layout.preferredWidth: 20

                text:"+"
                width: parent.buttonWidth

                onPressed: {
                    distanceManager.step = 0.1
                    timerIncrement.start()
                    timerIncrement.numberOfTriggerSinceStart = 0
                }

                onReleased: {
                    distanceManager.step = 0.1
                    timerIncrement.stop()
                }

                Timer {
                    id: timerIncrement
                    interval: 250;
                    repeat: true
                    triggeredOnStart: true

                    property int numberOfTriggerSinceStart: 0
                    onTriggered: {
                        numberOfTriggerSinceStart++

                        if (numberOfTriggerSinceStart >= 10)
                        {
                            distanceManager.step = 1;
                        }
                        if (numberOfTriggerSinceStart >= 20)
                        {
                            distanceManager.step = 10;
                        }
                        if (numberOfTriggerSinceStart >= 30)
                        {
                            distanceManager.step = 100;
                        }

                        distanceManager.incrementDistanceByStep()
                    }
                }
            }

            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: 20

                text:"-"
                width: parent.buttonWidth
                onClicked: distanceManager.decrementDistanceByStep()

                onPressed: {
                    timerDecrement.step = 0.1
                    timerDecrement.start()
                    timerDecrement.numberOfTriggerSinceStart = 0
                }

                onReleased: {
                    timerDecrement.step = 0.1
                    timerDecrement.stop()
                }

                Timer {
                    id: timerDecrement
                    interval: 250;
                    repeat: true
                    triggeredOnStart: true

                    property int numberOfTriggerSinceStart: 0
                    onTriggered: {
                        numberOfTriggerSinceStart++

                        if (numberOfTriggerSinceStart >= 10)
                        {
                            distanceManager.step = 1;
                        }
                        if (numberOfTriggerSinceStart >= 20)
                        {
                            distanceManager.step = 10;
                        }
                        if (numberOfTriggerSinceStart >= 30)
                        {
                            distanceManager.step = 100;
                        }

                        distanceManager.decrementDistanceByStep()
                    }
                }
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

    // Popup which allow to edit the distance
    Popup{
        id: popup

        margins: 0
        padding: 5
        contentHeight: childrenRect.height
        height: contentHeight

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        clip: true

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
            property int duration: 500

            ParallelAnimation{
                NumberAnimation { target: popup; property: "width"; from: 0; to: distanceWidget.width; duration: duration; easing.type: Easing.InOutQuad; easing.amplitude: 0.1}
                NumberAnimation { target: popup; property: "opacity";from: 0; to: 1; duration: duration; easing.type: Easing.InOutQuad }
            }
        }

        exit: Transition {
            property int duration: 500
            ParallelAnimation{

                NumberAnimation { target: popup; property: "width"; to: 0; from: distanceWidget.width; duration: duration; easing.type: Easing.InOutQuad; easing.amplitude: 0.1}
                NumberAnimation { target: popup; property: "opacity";to: 0; from: 1; duration: duration; easing.type: Easing.InOutQuad }
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

                    anchors.left: parent.left
                    anchors.right: parent.right

                    width: 50

                    validator: RegExpValidator {
                        regExp: /[0-9]*.+[0-9]+ *[A-Za-z]*/
                    }

                    onEditingFinished: {
                        console.log(acceptableInput)
                        // We don't want to close de popup when the textfield lose the focus
                        if (focus != false && popup.opened)
                        {
                            popup.close()
                        }
                    }

                    placeholderText: "ex: 25 km"

                    Button {
                        anchors.right: parent.right

                        width: 20
                        height: 20
                        text: "X"

                        background: Item {} // Allow to have en transparent background

                        onClicked: {
                            textInputEditText.text = "1 m"
                        }

                        onHoveredChanged: hovered ? contentItem.color = theme.colorHighlight : contentItem.color = "grey"
                    }
                }
            }
        }
    }
}


