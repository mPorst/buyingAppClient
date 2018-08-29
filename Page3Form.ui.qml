import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 600
    height: 400
    property alias port: port
    property alias host: host

    header: Label {
        text: qsTr("./Connection information")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        id: hostLabel
        text: qsTr("Server domain/IP")
        anchors.verticalCenterOffset: -131
        anchors.horizontalCenterOffset: -213
        font.pointSize: 10
        anchors.centerIn: parent
    }

    Text {
        id: host
        x: 34
        y: 73
        width: 228
        height: 35
        color: "#ffffff"
        text: qsTr("palaven.de")
        font.family: "Times New Roman"
        styleColor: "#ffffff"
        font.pixelSize: 22
    }

    Label {
        id: portLabel
        x: 3
        y: 3
        text: qsTr("port")
        anchors.verticalCenterOffset: -32
        anchors.horizontalCenterOffset: -253
        anchors.centerIn: parent
        font.pointSize: 10
    }

    Text {
        id: port
        x: 34
        y: 173
        width: 228
        height: 35
        color: "#ffffff"
        text: qsTr("39978")
        font.family: "Times New Roman"
        font.pixelSize: 22
        styleColor: "#ffffff"
    }
}
