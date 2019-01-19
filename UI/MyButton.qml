import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle{
    id:root

    color:"#0087cefa"


    property bool hovered:false
    property bool checked:false
    property url source:null
    property ExclusiveGroup group:null

    signal clicked

    border.width: 1
    border.color:"#0000bfff"

    onGroupChanged: {
        if(group)
            group.bindCheckable(root)
    }

    onCheckedChanged: {
        color = checked?"#8087cefa":"#0087cefa"
        border.color = checked?"#ff00bfff":"#0000bfff"
    }

    Image{
        id:image
        width:root.width
        height:root.height
        source:root.source
        opacity: root.enabled?1:0.4
        antialiasing: true
    }

    MouseArea{
        id: mouseArea
        anchors.fill: root
        hoverEnabled: true

        enabled: root.enabled

        onClicked: {
            root.checked = true
            root.clicked()
        }

        onHoveredChanged: {
            if(containsMouse){
                hovered = true
                root.border.color = "#8000bfff"
                root.color = checked?"#8087cefa":"#2087cefa"
            }
            else{
                root.hovered = false
                if(!checked)
                    root.border.color = "#0000bfff"
                root.color = checked?"#8087cefa":"#0087cefa"
                image.scale = 1
            }
        }

        onPressed: {
            //console.log("pressed")
            root.color = "#8087cefa"
            image.scale=0.8
        }

        onReleased: {
            image.scale = 1
        }

        /*
        onEntered: {
            root.hovered = true
            root.border.color = "#8000bfff"
        }

        onExited: {
            root.hovered = false
            root.border.color = "#0000bfff"
            root.color = checked?"#8087cefa":"#0087cefa"
        }*/
    }
}
