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
TARGET 	  = TD5

# fichiers sources/headers/ressources
SOURCES += main.cpp myglwidget.cpp planet.cpp \
    gameobject.cpp \
    ball.cpp \
    player.cpp \
    game.cpp
HEADERS += myglwidget.h planet.h \
    gameobject.h \
    animatedobject.h \
    ball.h \
    player.h \
    game.h

RESOURCES += \
    textures.qrc