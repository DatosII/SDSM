#-------------------------------------------------
#
# Project created by QtCreator 2015-09-15T00:16:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SDSM
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    SDSMMemoryNode/SDSMMemoryNode.cpp \
    Structures/Lists/memorylist.cpp \
    Structures/Nodes/memorynode.cpp \
    SDSMMemoryNode/servidorsmsmm.cpp

HEADERS += \
    SDSMMemoryNode/SDSMMemoryNode.h \
    Structures/Lists/memorylist.h \
    Structures/Nodes/memorynode.h \
    SDSMMemoryNode/servidorsmsmm.h

CONFIG += c++11
