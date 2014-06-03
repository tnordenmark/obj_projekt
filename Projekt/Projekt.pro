TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    song.cpp \
    album.cpp \
    jukebox.cpp \
    menu.cpp \
    menuitem.cpp \
    jukefunc.cpp \
    mytime.cpp

HEADERS += \
    song.h \
    album.h \
    jukebox.h \
    menu.h \
    menuitem.h \
    jukefunc.h \
    mytime.h

QMAKE_CXXFLAGS = -W -Wall -Wextra -pedantic -std=c++11
QMAKE_LFLAGS = -W -Wall -Wextra -pedantic -std=c++11
