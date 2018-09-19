import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 400
    height: 600

    property alias balanceButton: balanceButton
    property alias summaryButton: summaryButton
    property alias serverAnswerSummaryArea: serverAnswerSummaryArea

    header: Label {
        text: qsTr("./Übersicht")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Text {
        id: serverAnswerSummary
        objectName: "serverAnswerSummaryObject"
        x: 14
        y: 141
        width: 319
        height: 243
        text: qsTr("Serverantwort")
        font.pixelSize: 12

        Flickable
        {
        id: flickable
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick

        TextArea.flickable: TextArea {
            id: serverAnswerSummaryArea
            objectName: "serverAnswerSummaryAreaObject"
            text: qsTr("Text  Area")
            textFormat: Text.AutoText
            wrapMode: Text.WordWrap
            anchors.fill: parent
        }
        ScrollBar.vertical: ScrollBar { }
        }

    }

    Button {
        id: balanceButton
        objectName: "balanceButtonObject"
        x: 14
        y: 18
        text: "Guthaben"
    }

    Button {
        id: summaryButton
        objectName: "summaryButtonObject"
        x: 14
        y: 78
        text: "Zusammenfassung"
    }
}
