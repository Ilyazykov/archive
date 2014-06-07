#-------------------------------------------------
#
# Project created by QtCreator 2011-11-25T00:20:44
#
#-------------------------------------------------

QT       += core gui

TARGET = fisfeye
TEMPLATE = app

SOURCES +=\
        mainwindow.cpp \
    iprojectorfactory.cpp \
    main.cpp \
    mirrorprojector.cpp \
    nullprojector.cpp \
    cubeprojector.cpp \
    draw.cpp \
    stereographicsprojector.cpp \
    orthoprojector.cpp

HEADERS  += mainwindow.h \
    iprojectorfactory.h \
    iprojector.h \
    mirrorprojector.h \
    nullprojector.h \
    cubeprojector.h \
    draw.h \
    stereographicsprojector.h \
    orthoprojector.h

FORMS    += mainwindow.ui


