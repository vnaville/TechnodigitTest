import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.3
import QtQml 2.12
import "Theme"
import "BaseWidget"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Technodigit")

    BaseTheme{
        id: theme
    }

    Rectangle {
        id: root
        anchors.fill: parent
        color: theme.colorBackGround

        Column{
            anchors.fill: parent
            anchors.leftMargin: 50

            // separator
            Item{
                width: 100
                height: 100
            }

            Text{
                anchors.horizontalCenter:  parent.horizontalCenter

                textFormat: Text.RichText
                horizontalAlignment : Text.AlignHCenter
                verticalAlignment : Text.AlignVCenter

                text: "Enter a distance according to this format: <br> \" number distanceUnit\" <br> <b> Exemple: 25 km "
            }

            // separator
            Item{
                width: 100
                height: 50
            }

            DistanceWidget{
                id: distanceWidget
                anchors.horizontalCenter:  parent.horizontalCenter

                width: 200
                height: 50
            }

            // separator
            Item{
                width: 100
                height: 100
            }

            Text {
                id: descriptionText

                anchors.horizontalCenter:  parent.horizontalCenter

                Connections {
                    target: distanceWidget
                    onNewDistanceValidated: {
                        descriptionText.color = theme.textTheme.colorText
                        descriptionText.text = "The length is "+ distanceWidget.distance
                    }

                    onErrorOccurred:{
                        descriptionText.color = theme.textTheme.colorErrorText
                        descriptionText.text = "Error:" + errorString
                    }
                }
            }
        }
    }




}
