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
    Data_Access/xmlparser.cpp \
    Data_Access/pugixml/pugixml.cpp

HEADERS += \
    SDSMMemoryNode/SDSMMemoryNode.h \
    Data_Access/xmlparser.h \
    Data_Access/pugixml/pugixml.hpp \
    Data_Access/pugixml/pugiconfig.hpp \
    Structures/Lists/queue.h \
    Structures/Lists/linkedlist.h \
    Structures/Lists/dlinkedlist.h \
    Structures/Nodes/node_ll.h \
    Structures/Nodes/node_dll.h \
    Structures/Nodes/node_bst.h \
    Structures/Trees/binarytree.h
