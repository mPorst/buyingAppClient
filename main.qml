import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {

            writeButton.onClicked: {
                backend.initAndWriteSocket(price.text + '\n')
                serverAnswer.text = backend.readSocket()
                backend.closeSocket()
            }
        }

        Page2Form {

        }

        Page3Form{
            port.onTextChanged: {backend.setPort(port.text)}
            host.onTextChanged: {backend.setDomain(host.text)}
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
        TabButton {
            text: qsTr("Page 3")
        }
    }
}
