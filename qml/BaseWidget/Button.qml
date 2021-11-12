import QtQuick.Controls 2.12 as Control
import QtQuick 2.12
import "../BaseWidget"

Control.Button {
    id: button

    background: Rectangle {
                implicitWidth: 100
                implicitHeight: 40
                color: button.down ? "grey" : theme.colorBackGround2
                border.color: "#26282a"
                border.width: 1
                radius: 4
            }

    padding: 0

    contentItem: Text {
        text: parent.text
        color: button.hovered ? theme.colorHighlight : theme.textTheme.colorText
        font.pointSize: 12
        horizontalAlignment : Text.AlignHCenter
        verticalAlignment : Text.AlignVCenter
    }
}
