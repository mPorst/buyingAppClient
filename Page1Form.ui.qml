import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 600
    height: 400
    property alias serverAnswer: serverAnswer
    property alias writeButton: writeButton
    contentWidth: 0
    property alias price: price

    header: Label {
        text: qsTr("./Rechnung hochladen")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    TextEdit {
        id: price
        x: 26
        y: 35
        width: 210
        height: 61
        color: "#ffffff"
        text: qsTr("0.00")
        cursorVisible: true
        font.pixelSize: 22
    }

    Button {
        id: writeButton
        x: 275
        y: 120
        text: qsTr("send")
    }

    Label {
        id: label
        x: 26
        y: 7
        text: qsTr("Preis")
    }

    TextEdit {
        id: name
        x: 26
        y: 120
        width: 210
        height: 61
        color: "#ffffff"
        text: qsTr("Max Mustermann")
        font.pixelSize: 22
        cursorVisible: true
    }

    Label {
        id: label1
        x: 26
        y: 92
        text: qsTr("Name")
    }

    TextEdit {
        id: serverAnswer
        x: 26
        y: 231
        width: 210
        height: 99
        color: "#ffffff"
        text: qsTr("Keine")
        selectionColor: "#800063"
        cursorVisible: true
        font.pixelSize: 22
    }

    Label {
        id: label2
        x: 26
        y: 203
        text: qsTr("Serverantwort")
    }
}
