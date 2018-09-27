import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    id: page
    width: 600
    height: 400
    property alias port: port
    property alias host: host

    header: Label {
        text: qsTr("./Connection")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        id: hostLabel
        x: 34
        y: 40
        text: qsTr("Server domain/IP")
        font.pointSize: 10
    }

    TextEdit {
        id: host
        x: 34
        y: 73
        width: 228
        height: 35
        color: "#ffffff"
        text: qsTr("palaven.de")
        font.family: "Times New Roman"
        font.pixelSize: 22
    }

    Label {
        id: portLabel
        x: 34
        y: 138
        text: qsTr("port")
        font.pointSize: 10
    }

    TextEdit {
        id: port
        x: 34
        y: 173
        width: 228
        height: 35
        color: "#ffffff"
        text: qsTr("39978")
        font.family: "Times New Roman"
        font.pixelSize: 22
    }
}
