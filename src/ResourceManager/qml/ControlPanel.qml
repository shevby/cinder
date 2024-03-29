import QtQuick
import QtQuick.Controls
import Qt.labs.platform



Rectangle {
    width: parent.width
    height: 50
    color: "#e2e2e2"

    property var resourcesPath: resourcesPath

    Row {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter

        Button {
            text: "Browse"
            onClicked: {
                fileDialog.open();
            }
        }

        TextField {
            id: resourcesPath
            objectName: "resourcesPath"
            width: parent.width * 0.8
            enabled: false
        }
    }

    FolderDialog {
        id: fileDialog
        options: FileDialog.ReadOnly
        onAccepted: {
            resman.open(currentFolder.toString().slice(7));
        }
    }
}
