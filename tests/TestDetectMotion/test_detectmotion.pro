#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T11:26:13
#
#-------------------------------------------------

QT       -= gui

TARGET = test_detectmotion
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_detectmotion.cpp

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS +=-L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413

