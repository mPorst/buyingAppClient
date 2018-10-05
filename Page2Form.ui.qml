import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 800
    height: 480

    property alias balanceButton: balanceButton
    property alias summaryButton: summaryButton
    property alias serverAnswerSummaryArea: serverAnswerSummaryArea
    property alias eatersButton: eatersButton

    header: Label {
        text: qsTr("./Übersicht")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Text {
        id: serverAnswerSummary
        objectName: "serverAnswerSummaryObject"
        x: 271
        y: 18
        width: 433
        height: 336
        text: qsTr("Serverantwort")
        font.pixelSize: 12

        Flickable {
            id: flickable
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
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
            ScrollBar.vertical: ScrollBar {
            }
        }
    }

    Button {
        id: balanceButton
        objectName: "balanceButtonObject"
        x: 74
        y: 18
        text: "Guthaben anzeigen"
    }

    Button {
        id: summaryButton
        objectName: "summaryButtonObject"
        x: 74
        y: 102
        text: "Zusammenfassung"
    }

    Button {
        id: eatersButton
        x: 74
        y: 190
        text: qsTr("Wer hat gegessen ?")
    }
}
