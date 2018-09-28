import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 400
    height: 600
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
    property alias eatenCheckbox: eatenCheckbox

    //    property alias dateTextField: dateText.text
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
        height: 32
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
        id: nameField
        x: 26
        y: 101
        width: 210
        height: 32
        color: "#ffffff"
        text: qsTr("Max Mustermann")
        font.pixelSize: 22
        cursorVisible: true
    }

    Label {
        id: label1
        x: 26
        y: 73
        text: qsTr("Name")
    }

    TextEdit {
        id: serverAnswer
        objectName: "serverAnswerObject"
        x: 26
        y: 248
        width: 210
        height: 168
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
            anchors.bottomMargin: 0
            wrapMode: Text.WordWrap
            anchors.fill: parent
        }
    }

    Label {
        id: label2
        x: 26
        y: 209
        width: 94
        height: 22
        text: qsTr("Serverantwort")
    }

    TextEdit {
        id: dateText
        objectName: "dateTextObject"
        x: 152
        y: 32
        width: 123
        height: 38
        color: "#00fff0"
        text: qsTr("Text")
        font.pixelSize: 12
    }

    TextEdit {
        id: receiverField
        objectName: "receiverFieldObject"
        x: 25
        y: 167
        width: 210
        height: 32
        color: "#ffffff"
        text: qsTr("none")
        font.pixelSize: 22
        cursorVisible: true
    }

    Label {
        id: label4
        x: 25
        y: 139
        text: qsTr("Empfänger")
    }

    Button {
        id: reverseButton
        x: 26
        y: 429
        text: qsTr("Einkauf rückgängig")
        enabled: false
    }

    CheckBox {
        id: checkBox
        objectName: "checkBoxObject"
        x: 201
        y: 429
        text: qsTr("rückgängig?")
    }

    CheckBox {
        id: eatenCheckbox
        objectName: "eatenCheckboxObject"
        x: 218
        y: 209
    }

    Button {
        id: eatenButton
        x: 258
        y: 209
        text: qsTr("gegessen")
    }
}

/*##^## Designer {
    D{i:10;anchors_height:58;anchors_width:188;anchors_x:0;anchors_y:8}
}
 ##^##*/
