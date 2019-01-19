import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import hefengbin 1.0

Rectangle {
    id: toolBar

    height: 110
    color: "lightgray"

    property alias penColor:currentColor.color
    property alias penThickness:penThicknessSlider.value
    property alias currentTool:toolkit.toolType
    property alias rotateEnabled:rotateBtn.enabled
    property alias rotateDeg:rotateSlider.value
    property alias fillColor:fillColor.color

    ColorDialog{
        id:colorDialog
        onAccepted: {
            currentColor.color = colorDialog.color
        }
    }

    ColorDialog{
        id:fillDialog
        onAccepted: {
            fillColor.color = fillDialog.color
        }
    }

    ExclusiveGroup{
        id:toolkit
        property var toolType: DrawingArea.NONE
    }

    ExclusiveGroup{
        id:colorkit
    }

    Row{
        spacing: 1
        Rectangle{
            id: figure

            color:"whitesmoke"
            height: toolBar.height
            width: 222
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 3
                font.family: "Microsoft Yahei UI"
                text:"功能"
            }

            MyButton{
                id:clearBtn
                source:"icon/clear.png"
                width:32
                height:32
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10
                onClicked: {
                    checked = false
                    drawingArea.clear()
                }
            }

            MyButton{
                id:rotateBtn
                source:"icon/rotate.png"
                width:32
                height:32
                anchors.left: clearBtn.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10

                onClicked:{
                    checked = false
                    rotateDialog.open();
                }

                Dialog{
                    id: rotateDialog
                    title: "旋转角度"

                    Slider{
                        id:rotateSlider
                        maximumValue: 360
                        minimumValue: 0
                        stepSize: 1
                        width: 100
                    }

                    Text{
                        anchors.right: parent.right
                        text:"旋转角度为"+rotateSlider.value+"°"
                    }
                }
            }


            MyButton{
                id:offBtn
                source:"icon/3d.png"
                width:32
                height:32
                anchors.left: rotateBtn.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10
                onClicked: {
                    checked = false
                    drawingArea.displayOFF()
                }
            }

            MyButton{
                id:loadBtn
                source:"icon/load.png"
                width:32
                height:32
                anchors.left:offBtn.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10
                onClicked:{
                    checked = false
                    drawingArea.load()
                }
            }

            MyButton{
                id:saveBtn
                source:"icon/save.png"
                width:32
                height:32
                anchors.left: loadBtn.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10
                onClicked: {
                    checked = false
                    drawingArea.save()
                }
            }
        }

        Rectangle{
            id:tools

            color:"whitesmoke"
            height:toolBar.height
            width:230
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 3
                font.family: "Microsoft Yahei UI"
                text:"工具"
            }

            Grid{
                id:toolsGrid
                columns:5
                anchors.centerIn: parent
                anchors.verticalCenterOffset:-10

                spacing:10
                property var toolNameList:["select", "pencil", "eraser", "fill", "clip"]
                property var toolTypeList:[DrawingArea.SELECT,DrawingArea.PENCIL, DrawingArea.ERASER,DrawingArea.FILL,DrawingArea.CLIP]

                Repeater{
                    model:toolsGrid.toolNameList.length
                    MyButton{
                        source:"icon/"+toolsGrid.toolNameList[index]+".png"
                        width:32
                        height:32
                        group:toolkit

                        onCheckedChanged: {
                            if(checked)
                                toolkit.toolType = toolsGrid.toolTypeList[index]
                        }
                    }
                }
            }
        }

        Rectangle{
            id:shapes

            color:"whitesmoke"
            height:toolBar.height
            width:226
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom:parent.bottom
                anchors.bottomMargin: 3
                font.family:"Microsoft Yahei UI"
                text:"形状"
            }

            Grid{
                id:shapesGrid
                columns: 5
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -10

                spacing:10
                property var shapeNameList:["line", "circle", "ellipse","polygon", "curve"]
                property var toolTypeList:[DrawingArea.LINE, DrawingArea.CIRCLE, DrawingArea.ELLIPSE, DrawingArea.POLYGON, DrawingArea.CURVE]

                Repeater{
                    model:shapesGrid.shapeNameList.length
                    MyButton{
                        source:"icon/"+shapesGrid.shapeNameList[index]+".png"
                        width: 32
                        height: 32
                        group:toolkit

                        onCheckedChanged:{
                            if(checked)
                                toolkit.toolType = shapesGrid.toolTypeList[index];
                        }
                    }
                }
            }
        }

        Rectangle{
            id:thickness

            color:"whitesmoke"
            height:toolBar.height
            width:85

            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 3
                font.family: "Microsoft Yahei UI"
                text: "粗细"
            }

            Dialog {
                id: penThicknessDialog
                title: "选择笔宽"

                Slider{
                    id:penThicknessSlider
                    tickmarksEnabled: true
                    value:1
                    maximumValue: 10
                    minimumValue: 1
                    stepSize: 1
                    width: 100
                }

                Text{
                    anchors.right: parent.right
                    text:"笔宽为"+penThicknessSlider.value
                }
            }

            Rectangle{
                id:penThicknessButton
                color:"#0087cefa"
                border.width: 1
                border.color:"#0000bfff"

                anchors.centerIn: parent
                anchors.verticalCenterOffset: -10
                Image{
                    source:"icon/thickness.png"
                    height: parent.height
                    width: parent.width
                }
                width:48
                height: 48

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        penThicknessDialog.open()
                    }
                    onHoveredChanged: {
                        if(containsMouse){
                            penThicknessButton.border.color = "#8000bfff"
                            penThicknessButton.color = "#2087cefa"
                        }
                        else{
                            penThicknessButton.border.color = "#0000bfff"
                            penThicknessButton.color = "#0087cefa"
                        }
                    }
                }
            }
        }

        Rectangle{
            id:colors

            color:"whitesmoke"
            height:toolBar.height
            width:341
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 3
                font.family: "Microsoft Yahei UI"
                text:"颜色"
            }

            Rectangle{
                id:currentColor
                property bool checked:false
                onCheckedChanged: {
                    border.color=(checked)?"#ff00bfff":"#0000bfff";
                }

                color:"#000000"
                border.width: 1
                border.color: "#0000bfff"

                anchors.top:colors.top
                anchors.topMargin: 10
                anchors.left: colors.left
                anchors.leftMargin: 10
                height:50
                width:50
                Component.onCompleted: {
                    colorkit.bindCheckable(currentColor)
                }

                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                    onClicked: {
                        parent.checked=true;
                        colorDialog.open()
                    }
                    onHoveredChanged: {
                        if(!parent.checked)
                            parent.border.color = containsMouse?"#8000bfff":"#0000bfff"
                    }
                }
            }

            Rectangle{
                id:fillColor

                property bool checked:false
                onCheckedChanged: {
                    border.color=(checked)?"#ff00bfff":"#0000bfff";
                }

                color:"#ffffff"
                border.width: 1
                border.color: "#0000bfff"

                anchors.top:colors.top
                anchors.topMargin: 10
                anchors.left: currentColor.right
                anchors.leftMargin: 10
                height:50
                width:50
                Component.onCompleted: {
                    colorkit.bindCheckable(fillColor)
                }



                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                    onClicked: {
                        parent.checked=true;
                        fillDialog.open()
                    }
                    onHoveredChanged: {
                        if(!parent.checked)
                            parent.border.color = containsMouse?"#8000bfff":"#0000bfff"
                    }
                }
            }

            Text{
                anchors.top:currentColor.bottom
                anchors.horizontalCenter: currentColor.horizontalCenter
                font.family: "Microsoft Yahei Light"
                text:"边界\n颜色"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        currentColor.checked=true;
                    }
                }
            }

            Text{
                anchors.top:fillColor.bottom
                anchors.horizontalCenter: fillColor.horizontalCenter
                font.family: "Microsoft Yahei Light"
                text:"填充\n颜色"
                MouseArea{
                    anchors.fill:parent
                    onClicked: {
                        fillColor.checked=true;
                    }
                }
            }

            Grid{
                id:colorGrid

                anchors.right: colors.right
                anchors.rightMargin: 10
                anchors.top:colors.top
                anchors.topMargin: 13
                columns: 7
                spacing: 1

                property var colorList:["#ffffff", "#c3c3c3", "#585858", "#000000", "#88001b", "#ec1c24",
                    "#ff7f27", "#ffca18", "#fdeca6", "#fff200", "#c4ff0e", "#0ed145",
                    "#8cfffb", "#00a8f3"]

                Repeater{
                    model:colorGrid.colorList.length

                    Rectangle{
                        color:colorGrid.colorList[index]

                        height: 27
                        width: 27
                        border.width: 1
                        border.color: "#0000bfff"
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onHoveredChanged: {
                                parent.border.color = containsMouse?"#ff00bfff":"#0000bfff"
                            }
                            onClicked: {
                                //fillColor.color = colorGrid.colorList[index]
                                if(fillColor.checked)
                                    fillColor.color=colorGrid.colorList[index]
                                else
                                    currentColor.color=colorGrid.colorList[index]
                            }
                        }
                    }
                }
            }
        }

        Rectangle{
            id:blank
            height: toolBar.height
            width:toolBar.width - colors.x - colors.width
            color: "whitesmoke"
        }
    }
}
