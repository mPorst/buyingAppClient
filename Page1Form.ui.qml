import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 800
    height: 480
    property alias serverAnswer: serverAnswer
    property alias writeButton: writeButton
    property alias dateText: dateText
    contentWidth: 0
    property alias price: price
    property alias nameField: nameField
    property alias receiverField: receiverField
    property alias reverseButton: reverseButton
    property alias checkBox: checkBox
    property alias eatenButton: eatenButton
    property alias eatenCheckBox: eatenCheckbox

    //    property alias dateTextField: dateText.text
    header: Label {
        text: qsTr("./Rechnung hochladen")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    TextEdit {
        id: price
        x: 26
        y: 55
        width: 210
        height: 32
        color: "#ffffff"
        text: qsTr("0.00")
        cursorVisible: false
        font.pixelSize: 22
    }

    Button {
        id: writeButton
        objectName: "writeButtonObject"
        x: 620
        y: 55
        text: qsTr("sende Rechnung")
    }

    Label {
        id: label
        x: 26
        y: 27
        text: qsTr("Preis")
    }

    TextEdit {
        id: nameField
        x: 26
        y: 121
        width: 210
        height: 32
        color: "#ffffff"
        text: qsTr("Max Mustermann")
        font.pixelSize: 22
        cursorVisible: false
    }

    Label {
        id: label1
        x: 26
        y: 93
        text: qsTr("Name")
    }

    TextEdit {
        id: serverAnswer
        objectName: "serverAnswerObject"
        x: 26
        y: 188
        width: 548
        height: 165
        color: "#ffffff"
        text: qsTr("")
        textFormat: Text.AutoText
        selectionColor: "#800063"
        cursorVisible: true
        font.pixelSize: 16

        TextArea {
            id: serverAnswerArea
            objectName: "serverAnswerAreaObject"
            text: qsTr("Keine")
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            wrapMode: Text.WordWrap
            anchors.fill: parent
        }
    }

    Label {
        id: label2
        x: 26
        y: 160
        width: 94
        height: 22
        text: qsTr("Serverantwort")
    }

    TextEdit {
        id: dateText
        objectName: "dateTextObject"
        x: 364
        y: 27
        width: 123
        height: 38
        color: "#00fff0"
        text: qsTr("date")
        font.pixelSize: 12
    }

    TextEdit {
        id: receiverField
        objectName: "receiverFieldObject"
        x: 364
        y: 121
        width: 210
        height: 32
        color: "#ffffff"
        text: qsTr("none")
        font.pixelSize: 22
        cursorVisible: false
    }

    Label {
        id: label4
        x: 364
        y: 93
        text: qsTr("Empfänger")
    }

    Button {
        id: reverseButton
        x: 589
        y: 321
        text: qsTr("Einkauf rückgängig")
        enabled: false
    }

    CheckBox {
        id: checkBox
        objectName: "checkBoxObject"
        x: 589
        y: 267
        text: qsTr("rückgängig?")
    }

    CheckBox {
        id: eatenCheckbox
        objectName: "eatenCheckboxObject"
        x: 580
        y: 121
    }

    Button {
        id: eatenButton
        x: 620
        y: 121
        text: qsTr("gegessen")
    }
}

/*##^## Designer {
    D{i:10;anchors_height:58;anchors_width:188;anchors_x:0;anchors_y:8}
}
 ##^##*/
