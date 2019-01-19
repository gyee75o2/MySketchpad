QT += quick
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Shape/Circle.cpp \
    src/Shape/Ellipse.cpp \
    src/Shape/Line.cpp \
    src/Shape/Polygon.cpp \
    src/Shape/Shape.cpp \
    src/Tool/CircleTool.cpp \
    src/Tool/EllipseTool.cpp \
    src/Tool/EraserTool.cpp \
    src/Tool/FillTool.cpp \
    src/Tool/LineTool.cpp \
    src/Tool/PencilTool.cpp \
    src/Tool/PolygonTool.cpp \
    src/Tool/Tool.cpp \
    src/Common.cpp \
    src/DrawingArea.cpp \
    src/MyPainter.cpp \
    main.cpp \
    src/OFFViewer/GLwidget.cpp \
    src/OFFViewer/OFFModel.cpp \
    src/Tool/ClipTool.cpp \
    src/Tool/CurveTool.cpp \
    src/Tool/SelectTool.cpp \
    src/Shape/Curve.cpp \
    src/Shape/Rectangle.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/Shape/Circle.h \
    include/Shape/Ellipse.h \
    include/Shape/Line.h \
    include/Shape/Polygon.h \
    include/Shape/Shape.h \
    include/Tool/CircleTool.h \
    include/Tool/EllipseTool.h \
    include/Tool/EraserTool.h \
    include/Tool/FillTool.h \
    include/Tool/LineTool.h \
    include/Tool/PencilTool.h \
    include/Tool/PolygonTool.h \
    include/Tool/Tool.h \
    include/Common.h \
    include/DrawingArea.h \
    include/MyPainter.h \
    include/Tools.h \
    include/OFFViewer/GLWidget.h \
    include/OFFViewer/OFFModel.h \
    include/Tool/ClipTool.h \
    include/Tool/CurveTool.h \
    include/Tool/SelectTool.h \
    include/Shape/Curve.h \
    include/Shape/Rectangle.h
