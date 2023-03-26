import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: main

    visible: true

    width: 1280
    height: 720

    Rectangle {
        anchors.fill: parent

        ControlPanel {
            id: controlPanel
        }

        SplitView {
            anchors.top: controlPanel.bottom
            anchors.bottom: parent.bottom
            width: parent.width
            orientation: Qt.Horizontal
            Item {
                SplitView.fillWidth: true
                ResourceTree {
                    resourcesPath: controlPanel.resourcesPath
                }
            }

            Item {
                SplitView.maximumWidth: 3 * main.width / 4
                SplitView.minimumWidth: 300
                ResourceEditor {}
            }
        }
    }
}
