import QtQuick
import QtQuick.Controls




Rectangle {
    anchors.fill: parent
    anchors.margins: 10

    property var resourcesPath

    TreeView {
        id: treeView
        objectName: "treeView"
        anchors.fill: parent

        function setModel(m) {
            treeView.model = m;
        }

        delegate: Item {
            id: treeDelegate

            implicitWidth: padding + label.x + label.implicitWidth + padding
            implicitHeight: label.implicitHeight * 1.5

            readonly property real indent: 20
            readonly property real padding: 5

            // Assigned to by TreeView:
            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property int hasChildren
            required property int depth

            TapHandler {
                onTapped: treeView.toggleExpanded(row)
            }

            Text {
                id: indicator
                visible: treeDelegate.isTreeNode && treeDelegate.hasChildren
                x: padding + (treeDelegate.depth * treeDelegate.indent)
                anchors.verticalCenter: label.verticalCenter
                text: "▸"
                rotation: treeDelegate.expanded ? 90 : 0
            }

            Text {
                id: label
                x: padding + (treeDelegate.isTreeNode ? (treeDelegate.depth + 1) * treeDelegate.indent : 0)
                width: treeDelegate.width - treeDelegate.padding - x
                clip: true
                text: model.display
            }
        }

    }

    Connections {
        target: resman
        function onModelUpdated(path){
            resourcesPath.text = path;
            treeView.setModel(fsmodel);
        }
    }

    Component.onCompleted: {
        resman.defaults();
    }
}
