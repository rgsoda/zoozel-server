#-------------------------------------------------
#
# Project created by QtCreator 2010-11-24T12:25:44
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = zoozel-server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    player.cpp

HEADERS += \
    server.h \
    player.h
