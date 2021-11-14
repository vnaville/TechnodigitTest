import QtQuick 2.12


/* class holding propery used in the base Ui theme of the application */
Item
{
    readonly property color colorBackGround: "#2b2b2b"
    readonly property color colorBackGround2: "#333333"
    readonly property color colorHighlight: "cornflowerblue"
    readonly property color colorNoHighlight: "black"

    property alias textTheme: textTheme

    // Text theme
    Item {
        id: textTheme
        readonly property int textPixelSize: 14
        readonly property color colorText: "white"
        readonly property color colorErrorText: "red"
    }
}

