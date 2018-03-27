#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T11:26:13
#
#-------------------------------------------------

QT       -= gui

TARGET = TestOpenCV
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_open_cv.cpp

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS +=-L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413

