import QtQuick 2.6
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import hefengbin 1.0
import "./UI"

Window {
    id:root

    visible: true
    width: 1106
    height: 800
    title: qsTr("画图")
    color:"lightsteelblue"
    minimumHeight: 800
    maximumHeight: 800
    minimumWidth: 1106
    maximumWidth: 1106


    ToolBar{
        id: toolBar
        anchors.top:root.top
        width:parent.width
        rotateDeg: drawingArea.deg
        rotateEnabled: drawingArea.editing
    }

    Binding{
        target: drawingArea
        property: "deg"
        value:toolBar.rotateDeg
    }

    Rectangle{
        id:drawingBoard

        anchors.top:toolBar.bottom
        anchors.left:toolBar.left
        anchors.topMargin: 5
        anchors.leftMargin: 5
        color:"white"

        width:root.width - 30
        height:root.height - toolBar.height - 20

        DrawingArea{
            id:drawingArea
            anchors.fill:parent
            penColor: toolBar.penColor
            fillColor: toolBar.fillColor
            currentTool:toolBar.currentTool
            penThickness: toolBar.penThickness
            Component.onCompleted:init()
            /*
            Binding{
                target:toolBar
                property: "penThickness"
                value:drawingArea.penThickness
            }
            */
        }
    }
    /*
    DrawingArea{
        id:drawingArea
        anchors.top:toolBar.bottom
        anchors.left:toolBar.left
        anchors.topMargin: 5
        anchors.leftMargin: 5

        width:root.width - 30
        height:root.height - toolBar.height - 20
        penColor:toolBar.penColor
        currentTool: toolBar.currentTool
        Component.onCompleted: init();
    }
    */
    DropShadow {
        anchors.fill: drawingBoard
        horizontalOffset: 5
        verticalOffset: 5
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: drawingBoard
    }
}
