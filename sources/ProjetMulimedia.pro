# configuration Qt
QT       += core gui opengl widgets
CONFIG	 += c++14
TEMPLATE  = app

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
unix {
	LIBS     += -lGL -lGLU
}


# nom de l'exe genere
TARGET 	  = ProjetMultimedia

# fichiers sources/headers/ressources
SOURCES += main.cpp \
    ball.cpp \
    player.cpp \
    displayedobject.cpp \
    objectsmanager.cpp \
    collidingobject.cpp \
    animatedobject.cpp \
    limitwall.cpp \
    gameglwidget.cpp \
    deathwall.cpp \
    paddle.cpp \
    brick.cpp \
    detectmotion.cpp \
    level.cpp \
    game.cpp

HEADERS += \
    animatedobject.h \
    ball.h \
    player.h \
    displayedobject.h \
    objectsmanager.h \
    collidingobject.h \
    limitwall.h \
    gameglwidget.h \
    deathwall.h \
    paddle.h \
    brick.h \
    detectmotion.h \
    level.h \
    game.h

RESOURCES += \
    textures.qrc

FORMS +=

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413
