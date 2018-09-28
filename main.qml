import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    objectName: "mainWindow"
    visible: true
    width: 480
    height: 640
    title: qsTr("buying app")

    SwipeView {
        objectName: "swipeView"
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
            nameField.onTextChanged: {
                backend.setName(nameField.text)
            }

            writeButton.onClicked: {
                backend.sendPurchase(price.text, nameField.text ,dateText.text, receiverField.text)

            }
            checkBox.onCheckedChanged: {
                reverseButton.enabled = checkBox.checkState
            }
            reverseButton.onClicked: {
                backend.removePurchase(nameField.text, dateText.text, receiverField.text)
            }
            eatenButton.onClicked: {
                backend.sendConsumer(nameField.text, dateText.text, 'true')
            }
        }

        Page2Form {
            balanceButton.onClicked: {backend.getBalance()}
            summaryButton.onClicked: {backend.getSummary()}
        }

        Page3Form{
            port.onTextChanged: {backend.setPort(port.text)}
            host.onTextChanged: {backend.setDomain(host.text)}
            updateSwitch.onCheckedChanged: {backend.switchUpdate(updateSwitch.checked)}
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Rechnung")
        }
        TabButton {
            text: qsTr("Übersicht")
        }
        TabButton {
            text: qsTr("Server")
        }
    }
}
