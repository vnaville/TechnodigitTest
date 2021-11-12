import QtQuick.Controls 2.12 as Control
import QtQuick 2.12

Control.TextField {
    id: textField
    font.pointSize: theme.textTheme.textPixelSize

    color: "white"


    background: Rectangle {
        radius: 5
        color: theme.colorBackGround2
    }

    horizontalAlignment : Text.AlignHCente
    verticalAlignment : Text.AlignVCenter
}
